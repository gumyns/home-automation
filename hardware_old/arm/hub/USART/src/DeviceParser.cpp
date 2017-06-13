/*
 * DeviceParser.cpp
 *
 *  Created on: 31.12.2016
 *      Author: gumyns
 */

#include "DeviceParser.h"
#include <BlinkLed.h>
#include <cstdlib>
#include <functional>

namespace {

	static constexpr int ports = 4;
	/**
	 * Helper function that implements flow for finding pending interrupts and starting interrupt handling
	 *
	 * @return
	 */
	static int resolveInterrupts(DeviceSocket::State state, ::gumyns::sh::Socket & socket, DeviceSelector & selector) {
		// First check if there's interrupt pending and if not, skip
		if (!GPIO::A::read(GPIO::A::NOTIFIER)) return 1;
		// If socket is not idle, skip it
		if (state != DeviceSocket::State::IDLE) return 2;
		// If socket is idle, we need to find that device that caused interruption
		// First close socket and enable input on GPIO
		socket.close();
		// There are max of 8 devices per hub, so iterate over them to find interrupt source
		for (int i = 0; i < 8; i++) {
			selector.selectAddress(i, DeviceSelector::INTERRUPT);
			// check if there is high state on SCK line
			if(GPIO::A::read(GPIO::A::SCK)) {
				// Now change pin back to SCK
				selector.selectAddress(i, DeviceSelector::SPI);
				// Start SPI again
				socket.open();
				// Start sending in reading mode
				socket.send();
				return 0;
			}
		}
		return 3;
	}
}
DeviceParser::DeviceParser(DeviceSocket *socket): Parser(socket) {
	socket->setStateListener(this, &selector);
	Exti::initNotifier();

	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = EXTI4_15_IRQn;
	nvic.NVIC_IRQChannelPriority = 3;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

//	identStorage.push_back(new uint8_t[3]{0x00, 0x00, 0x33});
	identStorage.clear();
}

DeviceParser::~DeviceParser() {}

static inline void cleanBuffer(::gumyns::sh::Buffer<32> & buffer) {
	while(buffer.pending() >= 5 && buffer.peek(0) != DESCRIPTOR_H && buffer.peek(1) != DESCRIPTOR_L)
			buffer.pop();
}

::gumyns::sh::Frame* DeviceParser::retrieve() {
	using namespace ::gumyns::sh;

	// clear buffer from thrash before frame
	cleanBuffer(buffer);

	if (buffer.pending() >= 5) {
		// check if frame start
		if (buffer.peek(0) == DESCRIPTOR_H && buffer.peek(1) == DESCRIPTOR_L) {
			// check if complete frame is in buffer
			if (buffer.pending() > buffer.peek(2) + 2) {
				// just pop descriptor
				buffer.pop();
				buffer.pop();
				// pop size
				uint8_t frameSize = buffer.pop();
				uint8_t descriptor = buffer.pop();
				Frame * frame = new Frame((Order)(descriptor >> 5), descriptor & 0x1F);
				for (uint16_t i = 0; i < frameSize - 1; i++)
					frame->push(buffer.pop());
				// whatever it was, response is handled
				state = IDLE;
				if (!((*frame)[Frame::DESCRIPTOR] & 0xE0) && !hasIdent) {
					uint8_t *type = new uint8_t[3];
					for (int i = 0; i < 3; i++)
						type[i] = (*frame)[i];
					identStorage.push_back(type);
					delete frame;
					return nullptr;
				} else {
					hasIdent = false;
					return frame;
				}
			}
		}
	}
	return nullptr;
}

void DeviceParser::write(uint8_t byte) {
	buffer.push(byte);
}

void DeviceParser::send(::gumyns::sh::Frame * frame) {
	using namespace ::gumyns::sh;
	if (!((*frame)[Frame::DESCRIPTOR] & 0xE0) && !frame->isInternal()) {
		this->write(DESCRIPTOR_H);
		this->write(DESCRIPTOR_L);
		this->write(identStorage.size() * 3);
		auto it = identStorage.begin();
		while(it != identStorage.end()) {
			uint8_t *ident = *it++;
			for (int i = 0; i < 3; i++)
				this->write(ident[i]);
		}
		hasIdent = true;
	} else {
		selector.selectAddress((*frame)[Frame::DESCRIPTOR] & 0x1F, DeviceSelector::SPI);
		state = WRITING;
		getSocket().write(DESCRIPTOR_H);
		getSocket().write(DESCRIPTOR_L);
		Parser::send(frame);
	}
}

void DeviceParser::onFrameReceived(::gumyns::sh::Frame *frame) {
	frames.push(frame);
}

void DeviceParser::process() {
	if (frames.size() > 0 && socketState == DeviceSocket::State::IDLE) {
		::gumyns::sh::Frame *frame = frames.front();
		frames.pop();
		send(frame);
	}
}

void DeviceParser::onChange(DeviceSocket::State state) {
	if (state != DeviceSocket::State::INTERRUPT) { // Just state changed
		if(resolveInterrupts(state, getSocket(), selector)) {
			socketState = state;
		}
	} else { // Extra state for interrupt happened
		resolveInterrupts(socketState, getSocket(), selector);
	}
}

void DeviceParser::identify() {
	for (int i = 0; i < ports; i++) {
		onFrameReceived(::gumyns::sh::Frame::internal(::gumyns::sh::Order::IDENTIFY, i));
	}
}
