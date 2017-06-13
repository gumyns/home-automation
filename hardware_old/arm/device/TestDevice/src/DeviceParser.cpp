/*
 * DeviceParser.cpp
 *
 *  Created on: 31.12.2016
 *      Author: gumyns
 */

#include "DeviceParser.h"
#include <BlinkLed.h>
#include <cstdlib>

DeviceParser::~DeviceParser() {
	// TODO Auto-generated destructor stub
}

static inline void cleanBuffer(::gumyns::sh::Buffer<32> & buffer) {
	while(buffer.pending() > 2) {
		if (buffer.peek(0) == DESCRIPTOR_H && buffer.peek(1) == DESCRIPTOR_L) {
			if (buffer.peek(2) > 0x00  && buffer.peek(2) != 0xFF)
				break;
		}
		buffer.pop();
	}
}

::gumyns::sh::Frame* DeviceParser::retrieve() {
	using namespace ::gumyns::sh;

	// clear buffer from thrash before frame

	if (buffer.pending() >= 3) {
		while(!(USART1->ISR & USART_ISR_TXE));
			USART1->TDR = '>';
		for(int i = 0; i < buffer.pending(); i++) {
			char str[3];
			sprintf(str, "%02x", (int)buffer.peek(i));
			for(int j = 0; j< 2; j++) {
				while(!(USART1->ISR & USART_ISR_TXE));
					USART1->TDR = str[j];
			}
		}
		while(!(USART1->ISR & USART_ISR_TXE));
			USART1->TDR = '\r';
		while(!(USART1->ISR & USART_ISR_TXE));
			USART1->TDR = '\n';
		cleanBuffer(buffer);
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
				return frame;
			}
		}
	}
	return nullptr;
}

void DeviceParser::write(uint8_t byte) {
	buffer.push(byte);
}

void DeviceParser::send(::gumyns::sh::Frame * frame) {
	getSocket().write(DESCRIPTOR_H);
	getSocket().write(DESCRIPTOR_L);
	Parser::send(frame);
}
