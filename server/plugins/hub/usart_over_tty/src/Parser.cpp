#include "Parser.h"
#include <generated/PluginDescription.h>

Parser::Parser(nlohmann::json &json) {
	std::cout << "Parser()" << std::endl;
	if (json.find("connector") != json.end()) {
		connector = std::unique_ptr<Connector>(new Connector(*json.find("connector"), [this](uint8_t byte){
			buffer.push_back(byte);
			if (buffer.size() && buffer[0] != 0x39)
				buffer.clear();
			if (buffer.size() >= 3 && buffer.size() == buffer[2] + 3) {
				std::cout << "H<-";
				auto it = buffer.begin();
				while (it != buffer.end())
					std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(*it++) << ' ';
				std::cout << std::endl;

				std::vector<uint8_t> frame;
				std::copy(buffer.begin() + 3, buffer.end(), std::back_inserter(frame));
				if (listener)
					listener(0, frame); // it's usart, there won't be more than 1 hub at once, so address is 0
				this->buffer.clear();
			}
		}));
	} else {
		throw std::invalid_argument("Missing 'connector' object");
	}
}

void Parser::write(uint32_t address, std::vector<uint8_t> vector) {
	// begin of frame
	std::vector<uint8_t> response {0x00, 0x39, 0xa2};
	auto it = vector.begin();
	// add size of frame
	response.push_back(static_cast<uint8_t>(vector.size()));
	// add device frame
	while (it != vector.end())
		response.push_back(*it++);
	// just add '\0'
	response.push_back(0x00);
	// log it
	std::cout << "H->";
	it = response.begin();
	while (it != response.end())
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(*it++) << ' ';
	std::cout << std::endl;
	// pass it to connector
	connector->write(response);
}

void Parser::readListener(gumyns::sh::plugin::hub::Parser::FrameListener listener) {
	this->listener = listener;
}

Parser::~Parser() {
	std::cout << "~Parser()" << std::endl;
}

void Parser::identify(uint32_t address) {
	this->write(address, {0x00, 0x00});
}

uint32_t Parser::type() {
	return PluginDescription::ID;
}

