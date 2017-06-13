/*
 * DeviceManager.cpp
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#include "DeviceManager.h"
#include <BlinkLed.h>

namespace {
constexpr Timer::ticks_t SLEEP = Timer::FREQUENCY_HZ / 500; // 2ms

}

DeviceManager::DeviceManager(::gumyns::sh::Parser *parser) : parser(parser), device(nullptr) {
	timer.start();
}

void DeviceManager::setDevice(::gumyns::sh::Device * device) {
	this->device = device;
}

void DeviceManager::process() {
	uint16_t phase = 0; // 0..500, every 2ms
	// Infinite loop
	::gumyns::sh::Frame * framePtr;
	while (1) {
		timer.sleep(SLEEP);
		phase++;
		if (!(phase % 5)) { // every 10 ms
			while ((framePtr = parser->retrieve())) {
				device->write(framePtr);
			}
			while (device->process()) {
				if ((framePtr = device->read()))
					parser->send(framePtr);
				else
					break;
			}
		}
//		if (phase == 200)
//			BlinkLed::turnOn();
//		if (phase == 250)
//			BlinkLed::turnOff();
		if (phase > 500) {
			phase = 0;
		}
	}
}

::gumyns::sh::Socket::IRQ DeviceManager::externalIRQ(){
	return parser->getSocket().handler();
}

DeviceManager::~DeviceManager() {
	delete device;
	delete parser;
}

