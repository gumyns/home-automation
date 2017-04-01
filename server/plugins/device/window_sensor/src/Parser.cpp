#include "Parser.h"
#include <common.h>

class DeviceInfo {
public:
	const uint8_t channel;
	const std::string name;
	const uint8_t permission; // r - read, w - read + write

	DeviceInfo(uint8_t channel, const std::string name, uint8_t permission) : channel(channel), name(name), permission(permission) {}

	struct Permission {
		constexpr static uint8_t R = 0x01;
		constexpr static uint8_t W = 0x02;
		constexpr static uint8_t RW = 0x03;
	};
};

class Parser::Impl {
	std::vector<DeviceInfo> devices {
		DeviceInfo(0x00, "contact0", DeviceInfo::Permission::R),
		DeviceInfo(0x01, "contact1", DeviceInfo::Permission::R),
		DeviceInfo(0x02, "contact2", DeviceInfo::Permission::R),
		DeviceInfo(0x03, "contact3", DeviceInfo::Permission::R)
	};
public:
	Impl() {}

	~Impl() {}

	DeviceInfo* getDeviceInfo(uint8_t channel) {
		auto it = devices.begin();
		while(it != devices.end()) {
			if ((*it).channel == channel)
				return &*it;
			it++;
		}
		return nullptr;
	}
	nlohmann::json parseOutput(std::vector<uint8_t> &response) {
		nlohmann::json json;
		if(response.size() >= 2) {
			json["address"] = static_cast<int>(response[1]);
			auto array = nlohmann::json::array();
			auto it = response.begin();
			if (Desctiptor::order(*it++) == Desctiptor::RESPONSE) {
				uint8_t value = *it++;
				for (uint8_t i = 0; i < 4; i++) {
					nlohmann::json pair;
					pair[getDeviceInfo(i)->name] = static_cast<bool>(value & (0x01 << i));
					array.push_back(pair);
				}
			}
			json["r"] = array;
		}
		return json;
	}

	std::vector<uint8_t> parseInput(uint8_t address, nlohmann::json &json) {
		using namespace gumyns::sh::plugin::device;
		std::vector<uint8_t> request;
		if (json.find("r") != json.end() || json.find("w") != json.end()) {
			request.push_back(static_cast<uint8_t>((0x01 << 5) | address));
			return request;
		}
		return request;
	}
};

Parser::Parser(nlohmann::json &json) : gumyns::sh::plugin::device::Parser(), pImpl(new Impl()) {
	std::cout << "";
}


Parser::~Parser() {
	std::cout << "";
}

nlohmann::json Parser::parseOutput(std::vector<uint8_t> &response) {
	return pImpl->parseOutput(response);
}

std::vector<uint8_t> Parser::parseInput(uint8_t address, nlohmann::json &json) {
	return pImpl->parseInput(address, json);
}

uint32_t Parser::type() {
	return 0x0011;
}
