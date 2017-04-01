#ifndef GUMYNS_SMART_HOME_HUB_H
#define GUMYNS_SMART_HOME_HUB_H

#include <functional>
#include <utils/utils.h>
#include <hub/Plugin.h>
#include <utils/Logger.h>

namespace gumyns {
namespace sh {

	class Gateway {
	public:
		// Basically returns: Gateway, Hub address and frame
		typedef std::function<void(Gateway &, uint32_t, std::vector<uint8_t>)> Listener;
	private:
		POINTERS(Gateway)

		uint32_t id;
		plugin::hub::Parser::uPtr parser;
		Listener listener;
	public:
		Gateway(uint32_t id, plugin::hub::Parser::uPtr &parser, Listener& listener) : id(id), parser(std::move(parser)), listener(listener) {
			this->parser->readListener([&](uint32_t hubAddress, std::vector<uint8_t> frame) {
				if (this->listener) this->listener(*this, hubAddress, frame);
			});
			LogD << "Added gateway with id [" << id << "] of type [" << getType() <<  "]" << std::endl;
		}

		uint32_t getId() const {
			return id;
		}

		uint32_t getType() const {
			return this->parser->type();
		}

		void write(uint32_t address, std::vector<uint8_t> request) {
			this->parser->write(address, request);
		}

		void identify(uint32_t address) {
			this->parser->identify(address);
		}

		~Gateway() {

		}
	};

}}


#endif //GUMYNS_SMART_HOME_HUB_H
