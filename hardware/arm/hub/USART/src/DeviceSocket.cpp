/*
 * DeviceSocket.cpp
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#include "DeviceSocket.h"
#include "BlinkLed.h"
#include <config/EXTI.h>
#include <config/SPI.h>

namespace {
	static inline uint16_t hasInterrupt() {
		return GPIO::A::read(GPIO::A::NOTIFIER);
	}

	const static SPI::CR1::_CR1 CR1_BASE = SPI::CR1::MASTER | SPI::CR1::BIDIRECTIONAL_MODE | SPI::CR1::PRESCALLER;
	const static SPI::CR2::_CR2 CR2_BASE = SPI::CR2::RXNE | SPI::CR2::SS_HARDWARE | SPI::CR2::SS_PULSE | SPI::CR2::DATA_8_BIT;

	static inline void idleMode(DeviceSocket *socket) {
		SPI::CR1::reset();
		socket->setState(DeviceSocket::State::IDLE);
	}

	static inline void outputMode(DeviceSocket *socket) {
		SPI::CR1::set(CR1_BASE | SPI::CR1::BIDIRECTIONAL_OUTPUT);
		SPI::CR2::set(CR2_BASE | SPI::CR2::TXE);
		socket->setState(DeviceSocket::State::WRITING);
		SPI::CR1::enable(SPI::CR1::SPI);
	}

	static inline void inputMode(DeviceSocket *socket) {
		SPI::CR1::set(CR1_BASE);
		SPI::CR2::set(CR2_BASE);
		socket->setState(DeviceSocket::State::READ_DESCRIPTOR_H);
		SPI::CR1::enable(SPI::CR1::SPI);
	}
}

DeviceSocket::DeviceSocket() : stateListener(nullptr) {
	SPI::I2S::reset();
}

DeviceSocket::~DeviceSocket() {}

::gumyns::sh::Socket::IRQ DeviceSocket::handler() {
	SPI::CR2::disable(SPI::CR2::TXE);
	return [this]() {
		if (SPI::ISR::has(SPI::ISR::RXNE)) {
			uint16_t byte = SPI::read();
			switch (this->state) {
			case READ_DESCRIPTOR_H:
				this->state = byte == DESCRIPTOR_H ? READ_DESCRIPTOR_L : READ_DESCRIPTOR_H;
				if (--this->size == 0) {
					idleMode(this);
				}
				break;
			case READ_DESCRIPTOR_L:
				this->state = byte == DESCRIPTOR_H ? READ_DESCRIPTOR_L : byte == DESCRIPTOR_L ? READ_SIZE : READ_DESCRIPTOR_H;
				this->size = 4;
				break;
			case READ_SIZE:
				this->state = READ_ORDER;
				this->size = byte;
				break;
			case READ_ORDER:
				this->state = READ_DATA;
				byte |= (selector->currentAddress() & 0x1F);
				/* no break */
			default: // READ_DATA
				if (--this->size <= 0) {
					idleMode(this);
				}
			}
			listener(byte);
		}
		if (SPI::ISR::has(SPI::ISR::TXE)) {
			if (this->state == WRITING) {
				if (out.pending()) {
					SPI::write(out.pop());
				} else {
					while(SPI::ISR::has(SPI::ISR::BUSY));
					idleMode(this);
				}
			}
		}
		if (Exti::pending(Exti::NOTIFIER)) {
			uint16_t interrupt = hasInterrupt();
			Exti::clear(Exti::NOTIFIER);
			if (interrupt && stateListener) {
				stateListener->onChange(INTERRUPT);
			}
		}
	};
}

void DeviceSocket::write(uint8_t byte) {
	out.push(byte);
}

void DeviceSocket::send() {
	if (out.pending()) {
		out.push(0xFF);
		SPI::write(out.pop());
		outputMode(this);
	} else {
		inputMode(this);
		this->size = 4; // wait max 4 bytes for response
	}
}

void DeviceSocket::open() {
	GPIO::A::change(GPIO::PIN{GPIO::A::SCK, GPIO::PIN::AF, GPIO::PIN::PUSH_PULL, GPIO::PIN::HIGH, GPIO::PIN::PULL_DOWN});
	SPI::CR1::set(CR1_BASE | SPI::CR1::BIDIRECTIONAL_OUTPUT);
	SPI::CR2::set(CR2_BASE);

	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = SPI1_IRQn;
	nvic.NVIC_IRQChannelPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

bool DeviceSocket::idle() {
	return !out.pending(); // TODO shouln't be some flag?
}

void DeviceSocket::close() {
	SPI::CR1::reset();
	SPI::CR2::reset();
	GPIO::A::change(GPIO::PIN{GPIO::A::SCK, GPIO::PIN::IN, GPIO::PIN::PUSH_PULL, GPIO::PIN::HIGH, GPIO::PIN::PULL_DOWN});
}

void DeviceSocket::setState(State state) {
	this->state = state;
	if (stateListener)
		stateListener->onChange(state);
}
