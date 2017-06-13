#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>

namespace gumyns {
namespace sh {

/**
 * Simple implementation of circular buffer.
 *
 * Template parameter specifies size of this buffer;
 */
template <uint16_t SIZE>
class Buffer {
private:
	uint16_t read, write;

	uint8_t buffer[SIZE];
public:
	Buffer() : read(0), write(0) {
	};

	/**
	 * Adds next byte to end of buffer
	 *
	 * @param byte byte
	 */
	void push(uint8_t byte) {
		buffer[write++ % SIZE] = byte;
	}

	/**
	 * Reads byte but doesn't delete it from buffer.
	 *
	 * @param offset offset from current pointer
	 * @return byte from current position + offset
	 */
	uint8_t peek(uint16_t offset) {
		return buffer[(read + offset) % SIZE];
	}

	/**
	 * Reads one byte from buffer, removes it and returns.
	 *
	 * @return read byte from current pointer position
	 */
	uint8_t pop() {
		uint8_t ret = buffer[read % SIZE];
		buffer[read++ % SIZE] = 0;
		if (read == write)
			read = write = 0;
		return ret;
	}

	/**
	 * Returns size of buffer.
	 *
	 * @return size
	 */
	uint16_t size() {
		return SIZE;
	}

	/**
	 * Returns difference between pointers, basically it's amount of data in buffer.
	 *
	 * @return amount of pending bytes
	 */
	uint16_t pending() {
		return write - read;
	}

	virtual ~Buffer() {};
};
}
}
#endif // BUFFER_H
