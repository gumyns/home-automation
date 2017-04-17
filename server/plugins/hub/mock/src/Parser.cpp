#include "Parser.h"
#include <generated/PluginDescription.h>

class Parser::Impl {
	uint8_t addr0 = 1, addr4 = 0;
	short addr1 = 42;
	int addr2 = 0xFF00FF01;
	float addr3 = 36.6f;

	std::vector<uint8_t> buffer;

	gumyns::sh::plugin::hub::Parser::FrameListener listener;

public:
	void write(uint32_t address, std::vector<uint8_t> vector) {
		std::cout << address << " -> ";
		auto iter = vector.begin();
		while (iter != vector.end())
			std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(*iter++) << ' ';
		std::cout << std::endl;

		std::vector<uint8_t> response {0x04};
		auto it = vector.begin();
		while(it != vector.end()) {
			uint8_t order = *it++;
			if (order == 0x03) { // WRITE
				auto address = *it++;
				response.push_back(address);
				switch (address) {
					case 0x00: {
						addr0 = *it++;
						response.push_back(addr0);
					}
						break;
					case 0x01: {

					}
						break;
					case 0x02: {

					}
						break;
					case 0x03: {

					}
						break;
					case 0x04: {
						addr4 = *it++;
					}
						break;
					default:
						break;
				}
			} else {
				auto address = *it++;
				response.push_back(address);
				switch (address) {
					case 0x00: {
						response.push_back(addr0);
					}
						break;
					case 0x01: {
						response.push_back(addr1 >> 8 & 0xFF);
						response.push_back(addr1 & 0xFF);
					}
						break;
					case 0x02: {
						response.push_back(addr2 >> 24 & 0xFF);
						response.push_back(addr2 >> 16 & 0xFF);
						response.push_back(addr2 >> 8 & 0xFF);
						response.push_back(addr2 & 0xFF);
					}
						break;
					case 0x03: {

					}
						break;
					case 0x04: {
						response.push_back(addr4);
					}
						break;
					default:
						break;
				}

			}
		}
		this->listener(0, response);
	}

	void readListener(gumyns::sh::plugin::hub::Parser::FrameListener listener) {
		this->listener = listener;
	}

	~Impl() {

	}

	Impl(nlohmann::json &json) {

	}

	void identify(uint32_t address) {
		std::vector<uint8_t> response = {
				0x01, // descriptor
				0x00, 0x01, // switch on address 0
//			0x01, 0x02, // 16 bit int device on address 1
//			0x02, 0x03, // 32 bit int device on address 2
//			0x03, 0x04, // float device on address 3
//			0x04, 0x01  // another switch on address 1
		};
		this->listener(address, response); // just pass response
	}


};

Parser::Parser(nlohmann::json &json) : pImpl(new Parser::Impl(json)) {
	std::cout << json << std::endl;
}

void Parser::write(uint32_t address, std::vector<uint8_t> vector) {
	pImpl->write(address, vector);
}

void Parser::readListener(gumyns::sh::plugin::hub::Parser::FrameListener listener) {
	pImpl->readListener(listener);
}

Parser::~Parser() {

}

void Parser::identify(uint32_t address) {
	pImpl->identify(address);
}

uint32_t Parser::type() {
	return PluginDescription::ID;
}