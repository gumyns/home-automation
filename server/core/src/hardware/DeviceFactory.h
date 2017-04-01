#ifndef GUMYNS_SMART_HOME_DEVICEFACTORY_H
#define GUMYNS_SMART_HOME_DEVICEFACTORY_H

#include <utils/utils.h>
#include <hardware/model/PluginDescriptor.h>
#include <device/Plugin.h>

namespace gumyns {
namespace sh {

	class DeviceFactory {
		PIMPL(DeviceFactory)
	public:
		DeviceFactory(std::string);

		plugin::device::Parser::uPtr create(PluginDescriptor &);

		~DeviceFactory();
	};

}}


#endif //GUMYNS_SMART_HOME_DEVICEFACTORY_H
