/*
 * DeviceSocket.cpp
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#include "DeviceSocket.h"
#include <config/GPIO.h>
#include <config/SPI.h>

namespace {
	static inline void outputMode() {
		SPI::CR2::set(SPI::CR2::TXE | SPI::CR2::DATA_8_BIT);
		SPI::CR1::set(SPI::CR1::BIDIRECTIONAL_OUTPUT | SPI::CR1::BIDIRECTIONAL_MODE | SPI::CR1::SPI);
		GPIO::A::set(GPIO::A::NOTIFIER);
	}

	static inline void inputMode() {
		SPI::CR1::set(SPI::CR1::BIDIRECTIONAL_MODE);
		SPI::CR2::set(SPI::CR2::RXNE | SPI::CR2::DATA_8_BIT);
		SPI::CR1::enable(SPI::CR1::SPI);
	}
}

DeviceSocket::DeviceSocket() {
	SPI::I2S::reset();
}

DeviceSocket::~DeviceSocket() {}

::gumyns::sh::Socket::IRQ DeviceSocket::handler() {
	SPI::CR2::disable(SPI::CR2::TXE);
	return [this]() {
		if (SPI::ISR::has(SPI::ISR::RXNE)){
			uint16_t byte = SPI::read();
			if (mode == READING)
				listener(byte);
		}
		if (SPI::ISR::has(SPI::ISR::TXE)){
			if (out.pending()) {
				SPI::write(out.pop());
				GPIO::A::reset(GPIO::A::NOTIFIER);
			} else {
				inputMode();
				mode = READING;
			}
		}
	};
}

void DeviceSocket::write(uint8_t byte) {
	out.push(byte);
}

void DeviceSocket::send() {
	mode = WRITING;
	out.push(0);
	out.push(0);
	outputMode();
}

void DeviceSocket::open() {
	inputMode();

	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = SPI1_IRQn;
	nvic.NVIC_IRQChannelPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

bool DeviceSocket::idle() {
	return !out.pending(); // TODO shouldn't be some flag?
}

void DeviceSocket::close() {
	SPI::CR1::reset();
	SPI::CR2::reset();
}
