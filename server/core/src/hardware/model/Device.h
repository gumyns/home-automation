#ifndef GUMYNS_SMART_HOME_DEVICE_H
#define GUMYNS_SMART_HOME_DEVICE_H


#include <utils/utils.h>
#include <device/Plugin.h>

namespace gumyns {
namespace sh {

	class Device {
		POINTERS(Device)

		uint32_t id;
		plugin::device::Parser::uPtr parser;
	public:
		Device(uint32_t id, plugin::device::Parser::uPtr &parser) : id(id), parser(std::move(parser)) {
			LogD << "Added device: " << getType() << std::endl;
		}

		uint32_t getId() const {
			return id;
		}

		virtual nlohmann::json response(std::vector<uint8_t> &response) {
			return this->parser->parseOutput(response);
		}

		uint32_t getType() const {
			return this->parser->type();
		}

		virtual std::vector<uint8_t> request(uint8_t address, nlohmann::json json) {
			return this->parser->parseInput(address, json);
		}


		~Device() {

		}
	};

}}


#endif //GUMYNS_SMART_HOME_DEVICE_H
