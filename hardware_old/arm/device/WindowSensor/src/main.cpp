#include <stdio.h>
#include <stdlib.h>
#include <config/Config.h>
#include <DeviceSocket.h>

#include <DeviceParser.h>
#include <DeviceManager.h>
#include <WindowSensor.h>
#include <BlinkLed.h>

// Definitions visible only within this translation unit.
namespace {
	constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
	constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

::gumyns::sh::Socket::IRQ externalIRQ, deviceIRQ;

extern "C" {
	void SPI1_IRQHandler() {
		if (externalIRQ) {
			externalIRQ();
		}
	}
	void EXTI0_1_IRQHandler() {
		if (deviceIRQ) {
			deviceIRQ();
		}
	}
}

int main(int argc, char* argv[]) {
	Config::init();

	DeviceManager manager(new DeviceParser(new DeviceSocket()));
	externalIRQ = manager.externalIRQ();
	WindowSensor *sensor = new WindowSensor(0x00);
	deviceIRQ = sensor->handler();
	manager.setDevice(sensor);
	manager.process();
	delete sensor;
}

#pragma GCC diagnostic pop
