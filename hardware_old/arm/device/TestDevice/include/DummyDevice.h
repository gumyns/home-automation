/*
 * DummyDevice.h
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#ifndef DUMMYDEVICE_H_
#define DUMMYDEVICE_H_

#include <lib/Device.h>
#include "BlinkLed.h"

class DummyDevice: public virtual ::gumyns::sh::Device {
	bool state = true;

	bool readPending = false;

	uint8_t channel;
	
	BlinkLed led;
public:
	DummyDevice(uint8_t);

	virtual ~DummyDevice();

	virtual ::gumyns::sh::Frame *read();

	virtual void write(::gumyns::sh::Frame *);

	virtual bool process();
};

#endif /* DUMMYDEVICE_H_ */
