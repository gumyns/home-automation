/*
 * ExternalSocket.h
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#ifndef EXTERNALSOCKET_H_
#define EXTERNALSOCKET_H_

#include <lib/Socket.h>
#include <lib/Device.h>
#include <lib/Buffer.h>
#include <stm32f0xx_conf.h>

class ExternalSocket : public virtual ::gumyns::sh::Socket {
	::gumyns::sh::Buffer<96> out;
public:
	ExternalSocket();
	virtual ~ExternalSocket();

	virtual ::gumyns::sh::Socket::IRQ handler();

	virtual void write(uint8_t);

	virtual void send();

	virtual void open();

	virtual bool idle();

	virtual void close();
};

#endif /* EXTERNALSOCKET_H_ */
