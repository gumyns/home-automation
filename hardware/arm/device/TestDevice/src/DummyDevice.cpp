/*
 * DummyDevice.cpp
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#include "DummyDevice.h"

using namespace ::gumyns::sh;

DummyDevice::DummyDevice(uint8_t channel) :
		channel(channel) {
}

DummyDevice::~DummyDevice() {
}

Frame* DummyDevice::read() {
	if(this->responses.front()) {
		Frame * frame = responses.front();
		responses.pop();
		return frame;
	}
	return nullptr;
}

void DummyDevice::write(::gumyns::sh::Frame* frame) {
	this->requests.push(frame);
}

bool DummyDevice::process() {
	Frame * frame;
	bool ret = false;
	while(this->requests.size()) {
		switch((Order)(*this->requests.front())[Frame::DESCRIPTOR] >> 5) {
		case IDENTIFY:
			frame = new Frame(IDENTIFY, (*this->requests.front())[Frame::DESCRIPTOR] & 0x1F);
			frame->push(0x00);
			frame->push(0x02);
			responses.push(frame);
			delete this->requests.front();
			this->requests.pop();
			ret = true;
			break;
		case READ:
			frame = new Frame(RESPONSE, (*this->requests.front())[Frame::DESCRIPTOR] & 0x1F);
			frame->push(0x00); // channel
			frame->push(state);
			responses.push(frame);
			delete this->requests.front();
			this->requests.pop();
			ret = true;
			break;
		case WRITE:
			frame = new Frame(RESPONSE, (*this->requests.front())[Frame::DESCRIPTOR] & 0x1F);
			this->state = (*this->requests.front())[Frame::DESCRIPTOR + 2];
			if (this->state)
				led.turnOn();
			else
				led.turnOff();
			frame->push(0x00); // channel
			frame->push(state);
			responses.push(frame);
			delete this->requests.front();
			this->requests.pop();
			ret = true;
			break;
		default:
			delete this->requests.front();
			this->requests.pop();
		}
	}
	return ret;
}
