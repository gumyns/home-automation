#ifndef DEVICE_SELECTOR_H_
#define DEVICE_SELECTOR_H_

#include <config/GPIO.h>

class DeviceSelector {
public:
	enum Mode { SPI = 0, INTERRUPT = 1 };
private:
	constexpr static uint16_t MASK = 0x0F;

	uint16_t address; // TODO replace with bare port?

public:
	DeviceSelector() : address(0) {};
	~DeviceSelector() {};

	inline uint8_t currentAddress() { return address >> 1; }

	inline Mode currentMode() { return address & 0x01 ? INTERRUPT : SPI; }

	inline void selectAddress(uint8_t address, Mode mode) {
		this->address = (address << 1) + mode;
		GPIO::A::writePort(this->address >> 1, MASK);
	}

};

#endif
