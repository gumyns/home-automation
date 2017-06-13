#ifndef DEVICEPARSER_H_
#define DEVICEPARSER_H_

#include <FrameManager.h>
#include <lib/Parser.h>
#include <config/EXTI.h>
#include <DeviceSocket.h>
#include <DeviceSelector.h>

class DeviceParser:
		public virtual gumyns::sh::Parser,
		public virtual FrameManager,
		public virtual DeviceSocket::StateListener
{
private:
	enum Stage {
		READ_FRAME, // read first 3 bytes of frame
		READ_DATA,  // size is knows - read rest of data
		IDLE, 		// nothing is going on atm
		WRITING 	// writing data to device
	};

	Stage state = IDLE;

	DeviceSelector selector;

	DeviceSocket::State socketState = DeviceSocket::State::IDLE;

	std::vector<uint8_t *> identStorage;

	bool hasIdent = false;

	virtual void write(uint8_t);
public:
	DeviceParser(DeviceSocket *);

	virtual ~DeviceParser();

	virtual ::gumyns::sh::Frame * retrieve();

	virtual void send(::gumyns::sh::Frame *);

	virtual void onFrameReceived(::gumyns::sh::Frame *);

	virtual void process();

	virtual void onChange(DeviceSocket::State);

	virtual void identify();
};

#endif /* DEVICEPARSER_H_ */
