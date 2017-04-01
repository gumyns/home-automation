#ifndef GUMYNS_SMART_HOME_ADDRESSCONVERTER_H
#define GUMYNS_SMART_HOME_ADDRESSCONVERTER_H

#include <json.hpp>
#include <utils/Logger.h>

namespace gumyns {
namespace sh {

	class AddressConverter {
	public:

		static uint64_t fromFrame(void * frame) {
			uint8_t * byteFrame = static_cast<uint8_t *>(frame);
			uint64_t addr = 0;
			for (int i = 0; i < 6; i++) addr = (addr << 8) + (int)byteFrame[i + 1];
			return addr;
		}

		static nlohmann::json toJson(uint64_t address) {
			nlohmann::json json;
			try {
				json["gateway"] = (address >> 32) & 0xFFFF;
				json["hub"] = (address >> 16)  & 0xFFFF;
				json["device"] = address & 0xFFFF;
			} catch (std::exception &e) {
				LogE << "Parse error:" << e.what();
			}
			return json;
		}

		static uint64_t fromJson(nlohmann::json &json) {
			uint64_t addr = 0;
			try {
				addr += (uint64_t)json["gateway"];
				addr <<= 16;
				addr += (uint64_t)json["hub"];
				addr <<= 16;
				addr += (uint64_t)json["device"];
			} catch (std::exception &e) {
				LogE << "Parse error: " << json << " cause: "<< e.what();
				return 0;
			}
			return addr;
		}
	};

}}
#endif //GUMYNS_SMART_HOME_ADDRESSCONVERTER_H
