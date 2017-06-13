/*
 * DeviceManager.h
 *
 *  Created on: 28.12.2016
 *      Author: gumyns
 */

#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include <vector>
#include <lib/Device.h>
#include <lib/Parser.h>
#include "Timer.h"

class DeviceManager {
	::gumyns::sh::Parser * parser;

	::gumyns::sh::Device * device;

	Timer timer;

public:
	DeviceManager(::gumyns::sh::Parser *);

	void setDevice(::gumyns::sh::Device *);

	void process();

	::gumyns::sh::Socket::IRQ externalIRQ();

	virtual ~DeviceManager();
};

#endif /* DEVICEMANAGER_H_ */
