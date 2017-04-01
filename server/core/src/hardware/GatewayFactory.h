#ifndef GUMYNS_SMART_HOME_HUBFACTORY_H
#define GUMYNS_SMART_HOME_HUBFACTORY_H

#include <utils/utils.h>
#include <hardware/model/PluginDescriptor.h>
#include <hub/Plugin.h>

namespace gumyns {
namespace sh {

	class GatewayFactory {
		PIMPL(GatewayFactory)
	public:
		GatewayFactory(std::string);

		gumyns::sh::plugin::hub::Parser::uPtr create(PluginDescriptor &);

		~GatewayFactory();
 	};

}}

#endif //GUMYNS_SMART_HOME_HUBFACTORY_H
