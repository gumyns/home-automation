#include "GatewayFactory.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

class gumyns::sh::GatewayFactory::Impl {
	std::map<uint32_t, boost::shared_ptr<plugin::hub::ParserFactory>> factories;

	boost::filesystem::path path;
public:
	Impl(std::string path) : path(path) {}

	~Impl() {}

	gumyns::sh::plugin::hub::Parser::uPtr create(gumyns::sh::PluginDescriptor &descriptor) {
		auto factory = factories[descriptor.getType()];
		if (factory == nullptr) {
			factory = boost::dll::import<gumyns::sh::plugin::hub::ParserFactory>(
					path / descriptor.getName().c_str(), descriptor.getAlias().c_str(), boost::dll::load_mode::append_decorations
			);
			factories[descriptor.getType()] = factory;
		}
		nlohmann::json configuration = descriptor.getConfiguration();
		return factory->create(configuration);
	}
};

gumyns::sh::GatewayFactory::GatewayFactory(std::string path) : pImpl(new gumyns::sh::GatewayFactory::Impl(path)) {}

gumyns::sh::plugin::hub::Parser::uPtr gumyns::sh::GatewayFactory::create(gumyns::sh::PluginDescriptor &descriptor) {
	return pImpl->create(descriptor);
}

gumyns::sh::GatewayFactory::~GatewayFactory() {}
