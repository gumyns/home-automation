/*
 * FrameManager.cpp
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#include <Application.h>
#include <lib/Device.h>
// Definitions visible only within this translation unit.
namespace {
constexpr Timer::ticks_t SLEEP = Timer::FREQUENCY_HZ / 500; // 2ms
constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

Application::Application(::gumyns::sh::Parser * external, DeviceParser * device)
		: extParser(external), devParser(device), frameManager(device) {
	timer.start();
}

Application::~Application() {
	delete extParser;
	delete devParser;
}

::gumyns::sh::Socket::IRQ Application::extIRQ() {
	return extParser->getSocket().handler();
}

::gumyns::sh::Socket::IRQ Application::devIRQ() {
	return devParser->getSocket().handler();
}

void Application::main() {
	::gumyns::sh::Frame * framePtr;
	uint16_t phase = 0; // 0..500, every 2ms
	// sleep for 250ms
	timer.sleep(Timer::FREQUENCY_HZ / 4);
	// generate ident requests for every port... and store responses
	frameManager->identify();
	// Infinite loop
	while (1) {
		timer.sleep(SLEEP);
		phase++;
		if (!(phase % 5)) // every 10 ms
			while ((framePtr = devParser->retrieve()))
				extParser->send(framePtr);
			while ((framePtr = extParser->retrieve()))
				frameManager->onFrameReceived(framePtr);
			frameManager->process();
		if (phase == 200)
			BlinkLed::turnOn();
		if (phase == 250)
			BlinkLed::turnOff();
		if (phase > 500)
			phase = 0;
	}
}
