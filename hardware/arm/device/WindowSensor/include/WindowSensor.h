/*
 * DummyDevice.h
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#ifndef DUMMYDEVICE_H_
#define DUMMYDEVICE_H_

#include <lib/Device.h>

class WindowSensor: public ::gumyns::sh::Device {
	::gumyns::sh::Frame *response, *request;

	bool state = true;

	bool readPending = false;

	uint8_t channel;
public:
	WindowSensor(uint8_t);

	virtual ~WindowSensor();

	::gumyns::sh::Socket::IRQ handler();

	virtual ::gumyns::sh::Frame *read();

	virtual void write(::gumyns::sh::Frame *);

	virtual bool process();
};

#endif /* DUMMYDEVICE_H_ */
