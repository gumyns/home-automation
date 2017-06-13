#ifndef DEVICEPARSER_H_
#define DEVICEPARSER_H_

#include <lib/Parser.h>

class DeviceParser: public virtual gumyns::sh::Parser {
private:
	virtual void write(uint8_t);

	uint8_t inputBuf[2];

	uint16_t skip = 0;
public:
	DeviceParser(::gumyns::sh::Socket *socket): Parser(socket) {}
	virtual ~DeviceParser();

	virtual ::gumyns::sh::Frame * retrieve();

	virtual void send(::gumyns::sh::Frame * frame);
};

#endif /* DEVICEPARSER_H_ */
