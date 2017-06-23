#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <functional>
#include "Device.h"

namespace gumyns {
namespace sh {
class Socket {
public:
	/** Helper function pointer for IRQHandler implementation */
	typedef std::function<void(void)> IRQ;
	/** Byte listener, should be called in IRQ handler implementation */
	typedef std::function<void(uint8_t)> Listener;
protected:
	Listener listener;
public:
	Socket() = default;

	virtual ~Socket() {}

	virtual IRQ handler() = 0;

	void setListener(Listener listener) {
		this->listener = listener;
	}

	virtual void write(uint8_t) = 0;

	virtual void send() = 0;

	virtual void open() = 0;

	virtual bool idle() = 0;

	virtual void close() = 0;
};
}
}


#endif /* SOCKET_H_ */
