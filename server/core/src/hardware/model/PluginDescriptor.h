#ifndef GUMYNS_SMART_HOME_HUBDESCRIPTOR_H
#define GUMYNS_SMART_HOME_HUBDESCRIPTOR_H

#include <utils/utils.h>
#include <json.hpp>

namespace gumyns {
namespace sh {

	class PluginDescriptor {
		POINTERS(PluginDescriptor)

		uint32_t type;
		std::string name;
		nlohmann::json configuration;
	public:
		PluginDescriptor(nlohmann::json &json) {
			if (json.find("type") != json.end()) {
				type = *json.find("type");
			}
			if (json.find("name") != json.end()) {
				name = *json.find("name");
			}
			if (json.find("configuration") != json.end()) {
				configuration = *json.find("configuration");
			}
		}

		nlohmann::json serialize(){
			return {{
				{"type", type },
				{"name", name},
				{"configuration", configuration}
			}};
		}

		uint32_t getType() const {
			return type;
		}

		const std::string &getName() const {
			return name;
		}

		const nlohmann::json &getConfiguration() const {
			return configuration;
		}
	};

}
}

#endif //GUMYNS_SMART_HOME_HUBDESCRIPTOR_H
