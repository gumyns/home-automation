/*
 * DummyDevice.cpp
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#include <WindowSensor.h>
#include <config/GPIO.h>
#include <config/EXTI.h>
#include <BlinkLed.h>
#include <stm32f0xx_conf.h>

using namespace ::gumyns::sh;

namespace {
	static inline uint8_t readValue() {
		return GPIO::A::read(GPIO::A::SENSOR0);
	}
}

WindowSensor::WindowSensor(uint8_t channel) :
		channel(channel), request(nullptr), response(nullptr) {
	NVIC_InitTypeDef nvic;
	// Enable interrupt
	nvic.NVIC_IRQChannel = EXTI0_1_IRQn;
	nvic.NVIC_IRQChannelPriority = 3;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

WindowSensor::~WindowSensor() {
}

Frame* WindowSensor::read() {
	if(this->response) {
		Frame *ret = this->response;
		this->response = nullptr;
		return ret;
	}
	return nullptr;
}

void WindowSensor::write(::gumyns::sh::Frame* frame) {
	if (this->request) {
		delete request;
		this->request = nullptr;
	}
	this->request = frame;
}

bool WindowSensor::process() {
	Frame * frame;
	bool ret = false;
	if (this->response)
		return true;
	if(this->request) {
		switch((Order)(*this->request)[Frame::DESCRIPTOR] >> 5) {
		case IDENTIFY:
			BlinkLed::turnOn();
			frame = new Frame(IDENTIFY, 0);
			frame->push(0x00);
			frame->push(0x11);
			if (this->response) {
				delete response;
				this->response = nullptr;
			}
			ret = (response = frame);
			break;
		case READ:
		case WRITE:
			frame = new Frame(RESPONSE, 0);
			frame->push(readValue());
			if (this->response) {
				delete response;
				this->response = nullptr;
			}
			ret = (response = frame);
			break;
		default:
			delete this->request;
		}
	}
	if (this->request) {
		delete request;
		this->request = nullptr;
	}
	return ret;
}

::gumyns::sh::Socket::IRQ WindowSensor::handler() {
	Exti::init();
	return [this]() {
		Frame * frame;
		frame = new Frame(RESPONSE, 0);
		frame->push(readValue());
		if (this->response) {
			delete response;
			this->response = nullptr;
		}
		response = frame;
		Exti::clear(Exti::SENSOR0);
	};
}
