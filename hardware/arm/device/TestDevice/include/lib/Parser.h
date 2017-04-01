#ifndef PARSER_H_
#define PARSER_H_

#include "Frame.h"
#include "Buffer.h"
#include "Socket.h"

namespace gumyns {
namespace sh {

/**
 * Parser implementation useful for converting raw byte stream to frames, that are used widely in whole app.
 */
class Parser {
private:
	Socket *socket;
protected:
	Buffer<32> buffer;

	/**
	 * Entry point for byte stream for parser
	 *
	 * @param byte byte from RX channel or other input one
	 */
	virtual void write(uint8_t byte) = 0;
public:
	Parser(Socket * socket) : socket(socket) {
		socket->setListener([this](uint8_t byte){
			write(byte);
		});
		socket->open();
	}

	virtual ~Parser() {
		socket->close();
		delete socket;
	}

	/**
	 * Try to parse Frame, returns it if possible, or nullptr otherwise
	 */
	virtual Frame * retrieve() = 0;

	/**
	 * Will send Frame to attached socket
	 */
	virtual void send(Frame * frame) {
		socket->write(frame->getSize());
		for (int i = 0; i < frame->getSize(); i++) {
			socket->write((*frame)[i]);
		}
		delete frame;
		socket->send();
	}

	Socket& getSocket() {
		return (*socket);
	}
};
}
}

#endif /* DEVICEFRAME_H_ */
