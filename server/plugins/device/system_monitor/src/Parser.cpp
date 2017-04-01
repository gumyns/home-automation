#include "Parser.h"
#include <common.h>

enum Channel {
	THERMOMETER = 0x00
};

class DeviceInfo {
public:
	const uint8_t channel;
	const std::string name;
	const uint8_t permission; // r - read, w - read + write

	DeviceInfo(Channel channel, const std::string name, uint8_t permission) : channel(channel), name(name), permission(permission) {}

	struct Permission {
		constexpr static uint8_t R = 0x01;
		constexpr static uint8_t W = 0x02;
		constexpr static uint8_t RW = 0x03;
	};
};

class Parser::Impl {
	std::vector<DeviceInfo> devices {
		DeviceInfo(Channel::THERMOMETER, "temperature", DeviceInfo::Permission::R)
	};

public:
	static const uint16_t ID = 0x0001;

	Impl() {}

	~Impl() {}

	DeviceInfo* getDeviceInfo(uint8_t channel) {
		auto it = this->devices.begin();
		while(it != this->devices.end()) {
			if ((*it).channel == channel)
				return &*it;
			it++;
		}
		return nullptr;
	}

	DeviceInfo* getDeviceInfo(std::string name) {
		auto it = this->devices.begin();
		while(it != this->devices.end()) {
			if (std::strcmp((*it).name.c_str(), name.c_str()) == 0)
				return &*it;
			it++;
		}
		return nullptr;
	}

	nlohmann::json parseOutput(std::vector<uint8_t> &response) {
		using namespace gumyns::sh::plugin::device;
		nlohmann::json json;
		if(response.size() >= 2) {
			json["address"] = (int)Desctiptor::address(response[0]);
			auto array = nlohmann::json::array();
			auto it = response.begin();
			if (Desctiptor::order(*it++) == Desctiptor::RESPONSE) {
				while(it != response.end()) {
					if (auto info = getDeviceInfo(*it++)) {
						nlohmann::json pair;
						switch (info->channel) {
							case Channel::THERMOMETER:
								pair[info->name] = Short::deserialize(it);
								break;
							default:
								break;
						}
						if (!pair.empty())
							array.push_back(pair);
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
			request.push_back(Desctiptor::read(address));
			std::vector<std::string> endpoints = json["r"];
			auto it = endpoints.begin();
			while(it != endpoints.end())
				if(auto info = getDeviceInfo(*it++))
					if (info->permission & DeviceInfo::Permission::R)
						request.push_back(info->channel);
			return request;
		}
		if (json.find("w") != json.end()) {
			request.push_back(Desctiptor::write(address));
			nlohmann::json::array_t channels = json["w"];
			for (nlohmann::json::array_t::iterator it = channels.begin(); it != channels.end(); ++it) {
				nlohmann::json::iterator pair = (*it).begin();
				if (pair != (*it).end()) {
					if (auto info = getDeviceInfo(pair.key())) {
						if (info->permission & DeviceInfo::Permission::W) {
							switch (info->channel) {
								case Channel::THERMOMETER:
									appendVector(request, Chunk::create(info->channel, Short::serialize((short) pair.value().get<int>())));
									break;
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

Parser::Parser(nlohmann::json &json) : pImpl(new Impl()) {
	std::cout << "SystemMonitor device create" << std::endl;
}

Parser::~Parser() {
	std::cout << "SystemMonitor device delete" << std::endl;
}

nlohmann::json Parser::parseOutput(std::vector<uint8_t> &response) {
	return this->pImpl->parseOutput(response);
}

std::vector<uint8_t> Parser::parseInput(uint8_t address, nlohmann::json &json) {
	return this->pImpl->parseInput(address, json);
}

uint32_t Parser::type() {
	return Impl::ID;
}
