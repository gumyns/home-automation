#ifndef FRAME_H_
#define FRAME_H_

#include <stdio.h>
#include <functional>
#include <vector>

#define DESCRIPTOR_H 0x39
#define DESCRIPTOR_L 0xA2
#define BROADCAST_CHANNEL 0xFF

namespace gumyns {
namespace sh {

enum Order {
	IDENTIFY = 0x00,
	READ = 0x01,
	WRITE = 0x02,
	RESPONSE = 0x03
};

/**
 * Encapsulates frame format used during communication between device and hub, and vice versa.
 */
class Frame {
	std::vector<uint8_t> data;
public:
	constexpr static int DESCRIPTOR = 0;

	/**
	 * Creates frame
	 */
	Frame(Order order, uint8_t address) {
		data.push_back((order << 5) | address);
	}

	virtual ~Frame() {
		data.clear();
	}

	/**
	 * Size of whole frame.
	 *
	 * @return size of frame.
	 */
	uint8_t getSize() {
		return data.size();
	}

	void push(uint8_t byte) {
		data.push_back(byte);
	}

	/**
	 * Array operator for convenient API. Note, that it doens't return references, so Read-Only.
	 *
	 * @return specific field from frame.
	 */
	virtual uint8_t operator[](int i) {
		return data[i];
	}
};

}
}
#endif /* FRAME_H_ */
