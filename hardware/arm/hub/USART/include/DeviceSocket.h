#ifndef DEVICESOCKET_H_
#define DEVICESOCKET_H_

#include <lib/Socket.h>
#include <lib/Device.h>
#include <lib/Buffer.h>
#include <DeviceSelector.h>

class DeviceSocket: public virtual ::gumyns::sh::Socket {
public:
	enum State { IDLE, READ_DESCRIPTOR_H, READ_DESCRIPTOR_L, READ_SIZE, READ_ORDER, READ_DATA, WRITING, INTERRUPT };

	class StateListener {
	public:
		virtual ~StateListener() {};
		virtual void onChange(DeviceSocket::State) = 0;
	};
private:
	::gumyns::sh::Buffer<36> out;

	StateListener *stateListener;

	State state = IDLE;

	uint8_t size = 0;

	DeviceSelector *selector;
public:
	DeviceSocket();
	virtual ~DeviceSocket();

	virtual ::gumyns::sh::Socket::IRQ handler();

	virtual void write(uint8_t);

	virtual void send();

	virtual void open();

	virtual bool idle();

	virtual void close();

	inline void setState(State);

	inline void setStateListener(StateListener *listener, DeviceSelector *selector) {
		this->stateListener = listener;
		this->selector = selector;
	}
};

#endif /* DEVICESOCKET_H_ */
