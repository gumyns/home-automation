/*
 * HubParser.cpp
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#include "HubParser.h"
#include "stm32f0xx.h"

HubParser::~HubParser() {}

void HubParser::write(uint8_t byte) {
	using namespace ::gumyns::sh;

	buffer.push(byte);
	// DEBUG STUFF
//	if (byte == 'a') {
//		::gumyns::sh::Frame frame(::gumyns::sh::Order::IDENTIFY, 0);
//		buffer.push(DESCRIPTOR_H);
//		buffer.push(DESCRIPTOR_L);
//		buffer.push(frame.getSize());
//		for (uint16_t i = 0; i< frame.getSize(); i++)
//			buffer.push(frame[i]);
//	}
//	if (byte == 's') {
//		Frame frame(READ, 0x00);
//		buffer.push(DESCRIPTOR_H);
//		buffer.push(DESCRIPTOR_L);
//		buffer.push(frame.getSize());
//		for (uint16_t i = 0; i< frame.getSize(); i++)
//					buffer.push(frame[i]);
//	}
//	if (byte == 'd') {
//		Frame frame(WRITE, 0x00);
//		frame.push(0x12);
//		buffer.push(DESCRIPTOR_H);
//		buffer.push(DESCRIPTOR_L);
//		buffer.push(frame.getSize());
//		for (uint16_t i = 0; i< frame.getSize(); i++)
//			buffer.push(frame[i]);
//	}
}

::gumyns::sh::Frame* HubParser::retrieve() {
	using namespace ::gumyns::sh;

	if (buffer.pending() >= 3) {
		// clear buffer from thrash before frame
		while(buffer.pending() >= 3 && buffer.peek(0) != DESCRIPTOR_H && buffer.peek(1) != DESCRIPTOR_L)
			buffer.pop();
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
				return frame;
			}
		}
	}
	return nullptr;
}

void HubParser::send(::gumyns::sh::Frame * frame) {
	using namespace ::gumyns::sh;
	getSocket().write(DESCRIPTOR_H);
	getSocket().write(DESCRIPTOR_L);
	Parser::send(frame);
}
