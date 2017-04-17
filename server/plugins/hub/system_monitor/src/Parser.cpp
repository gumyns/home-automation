#include "Parser.h"
#include <fstream>
#include <common.h>
#include <generated/PluginDescription.h>

enum Channel {
	THERMOMETER = 0x00
};

class Parser::Impl {
	std::string temperatureFile;

	gumyns::sh::plugin::hub::Parser::FrameListener listener;
public:
	static const uint16_t ID = 0x0001;

	Impl(nlohmann::json &json) {
		if (json.find("temperature") != json.end()) {
			temperatureFile = json["temperature"];
		} else { // Fallback for NanoPi
			temperatureFile = "/sys/class/hwmon/hwmon1/temp1_input";
		}
	}

	~Impl() {}

	void identify(uint32_t address) {
		std::vector<uint8_t> response;
		// append device types available in this hub
		appendVector(response, Chunk::create(Desctiptor::identify(), Short::serialize(ID)));
		// pass response to server
		this->listener(address, response);
	}

	std::vector<uint8_t> handleTemperature(uint8_t order) {
		std::ifstream file;
		int temperature = 0;

		file.open(temperatureFile, std::ios::in | std::ios::binary);
		file >> temperature;
		file.close();

		return Chunk::create(Channel::THERMOMETER, Short::serialize(static_cast<short>(temperature)));
	}

	void write(uint32_t address, std::vector<uint8_t> vector) {
		std::vector<uint8_t> response;
		auto it = vector.begin();
		while(it != vector.end()) {
			uint8_t order = Desctiptor::order(*it);
			uint8_t address =  Desctiptor::address(*it++);
			response.push_back(Desctiptor::response(address));
			if (it == vector.end()) {
				appendVector(response, handleTemperature(order));
			} else {
				switch (static_cast<Channel>(*it++)) {
					case Channel::THERMOMETER:
						appendVector(response, handleTemperature(order));
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
};

Parser::Parser(nlohmann::json &json) : pImpl(new Parser::Impl(json)) {
	std::cout << json << std::endl;
}

void Parser::write(uint32_t address, std::vector<uint8_t> vector)  {
	pImpl->write(address, vector);
}

void Parser::readListener(gumyns::sh::plugin::hub::Parser::FrameListener listener) {
	pImpl->readListener(listener);
}

Parser::~Parser() {}

void Parser::identify(uint32_t address) {
	pImpl->identify(address);
}

uint32_t Parser::type() {
	return PluginDescription::ID;
}

