/*
 * HubParser.h
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#ifndef HUBPARSER_H_
#define HUBPARSER_H_

#include <lib/Parser.h>

class HubParser: public virtual gumyns::sh::Parser {
	uint16_t addr = 0;

	virtual void write(uint8_t);
public:
	HubParser(::gumyns::sh::Socket *socket): Parser(socket) {}

	virtual ~HubParser();

	virtual ::gumyns::sh::Frame * retrieve();

	virtual void send(::gumyns::sh::Frame *);
};

#endif /* HUBPARSER_H_ */
