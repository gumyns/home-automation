#ifndef DEVICESOCKET_H_
#define DEVICESOCKET_H_

#include <lib/Socket.h>
#include <lib/Device.h>
#include <lib/Buffer.h>



class DeviceSocket: public virtual ::gumyns::sh::Socket {
public:
	enum Mode { READING, WRITING };
private:
	DeviceSocket::Mode mode = READING;

	::gumyns::sh::Buffer<48> out;

	uint8_t skip = 0;
public:
	DeviceSocket();
	virtual ~DeviceSocket();

	virtual ::gumyns::sh::Socket::IRQ handler();

	virtual void write(uint8_t);

	virtual void send();

	virtual void open();

	virtual bool idle();

	virtual void close();
};

#endif /* DEVICESOCKET_H_ */
