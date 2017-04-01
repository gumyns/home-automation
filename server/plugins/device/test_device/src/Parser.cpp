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
		DeviceInfo(0x00, "status", DeviceInfo::Permission::RW),
		DeviceInfo(0x01, "temperature", DeviceInfo::Permission::R)
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

	DeviceInfo* getDeviceInfo(std::string name) {
		auto it = devices.begin();
		while(it != devices.end()) {
			if (std::strcmp((*it).name.c_str(), name.c_str()) == 0)
				return &*it;
			it++;
		}
		return nullptr;
	}

	nlohmann::json parseOutput(std::vector<uint8_t> &response) {
//		std::cout << "Response: " << toHexString(response) << std::endl;
		nlohmann::json json;
		if(response.size() >= 2) {
			json["address"] = (int)response[1];
			auto array = nlohmann::json::array();
			auto it = response.begin();
			if (Desctiptor::order(*it++) == Desctiptor::RESPONSE) {
				while(it != response.end()) {
					if (auto info = getDeviceInfo(*it++)) {
						switch (info->channel) {
							case 0x00: {
								nlohmann::json pair;
								pair[info->name] = (bool) (*it++);
								array.push_back(pair);
							}
								break;
							case 0x01: {
								nlohmann::json pair;
								uint8_t buffer[4];
								for (int i = 0; i < 4; i++) {
									buffer[i] = *it++;
								}
								float value;
								memcpy(&value, buffer, 4);
								pair[info->name] = value;
								array.push_back(pair);
							}
								break;
						}
					}
				}
			}
			json["r"] = array;
		}
		return json;
	}

	std::vector<uint8_t> parseInput(uint8_t address, nlohmann::json &json) {
		using namespace gumyns::sh::plugin::device;
		std::vector<uint8_t> request;
		if (json.find("r") != json.end()) {
			request.push_back((0x01 << 5) | address);
			std::vector<std::string> endpoints = json["r"];
			auto it = endpoints.begin();
			while(it != endpoints.end())
				if(auto info = getDeviceInfo(*it++))
					if (info->permission & DeviceInfo::Permission::R)
						request.push_back(info->channel);
			return request;
		}
		if (json.find("w") != json.end()) {
			request.push_back((0x02 << 5) | address);
			nlohmann::json::array_t channels = json["w"];
			for (nlohmann::json::array_t::iterator it = channels.begin(); it != channels.end(); ++it) {
				nlohmann::json::iterator pair = (*it).begin();
				if (pair != (*it).end()) {
					if (auto info = getDeviceInfo(pair.key())) {
						if (info->permission & DeviceInfo::Permission::R) {
							request.push_back(info->channel);
							switch (info->channel) {
								case 0x00: {
									request.push_back((uint8_t)pair.value().get<bool>());
								} break;
								case 0x01: {
									float f = (float) pair.value().get<double>();
									unsigned char const * p = reinterpret_cast<unsigned char const *>(&f);
									for (int i = 0; i < 4; i++)
										request.push_back(p[i]);
								} break;
								default:
									break;
							}
						}
					}
				}
			}
			return request;
		}
		return request;
	}
};

Parser::Parser(nlohmann::json &json) : gumyns::sh::plugin::device::Parser(), pImpl(new Impl()) {
	std::cout << "Parser() ->" << json << "<-" << std::endl;
}


Parser::~Parser() {
	std::cout << "~Parser()" << std::endl;
}

nlohmann::json Parser::parseOutput(std::vector<uint8_t> &response) {
	return pImpl->parseOutput(response);
}

std::vector<uint8_t> Parser::parseInput(uint8_t address, nlohmann::json &json) {
	return pImpl->parseInput(address, json);
}

uint32_t Parser::type() {
	return 0x0001;
}
