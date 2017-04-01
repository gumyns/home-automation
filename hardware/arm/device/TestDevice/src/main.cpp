#include <stdio.h>
#include <stdlib.h>
#include <config/Config.h>
#include <DeviceSocket.h>

#include <DeviceParser.h>
#include <DeviceManager.h>
#include <DummyDevice.h>

#include <ExternalSocket.h>

// Definitions visible only within this translation unit.
namespace {
	constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
	constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

::gumyns::sh::Socket::IRQ externalIRQ;

extern "C" {
	void SPI1_IRQHandler() {
		if (externalIRQ) {
			externalIRQ();
		}
	}
}

int main(int argc, char* argv[]) {
	Config::init();

	gumyns::sh::Socket *external = new ExternalSocket();
	external->open();

	DeviceManager manager(new DeviceParser(new DeviceSocket()));
	externalIRQ = manager.externalIRQ();
	manager.setDevice(new DummyDevice(0x00));
	manager.process();
	external->close();
}

#pragma GCC diagnostic pop
