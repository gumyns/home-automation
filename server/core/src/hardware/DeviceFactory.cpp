#include "DeviceFactory.h"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

class gumyns::sh::DeviceFactory::Impl {
	std::map<uint32_t, boost::shared_ptr<plugin::device::ParserFactory>> factories;

	boost::filesystem::path path;
public:
	Impl(std::string path) : path(path) {}

	~Impl() {}

	gumyns::sh::plugin::device::Parser::uPtr create(gumyns::sh::PluginDescriptor &descriptor) {
		auto factory = factories[descriptor.getType()];
		if (factory == nullptr) {
			factory = boost::dll::import<gumyns::sh::plugin::device::ParserFactory>(
                    path / descriptor.getName().c_str(), "pDevice", boost::dll::load_mode::append_decorations
			);
			factories[descriptor.getType()] = factory;
		}
		nlohmann::json configuration = descriptor.getConfiguration();
		return factory->create(configuration);
	}
};

gumyns::sh::DeviceFactory::DeviceFactory(std::string path) : pImpl(new gumyns::sh::DeviceFactory::Impl(path)) {}

gumyns::sh::plugin::device::Parser::uPtr gumyns::sh::DeviceFactory::create(gumyns::sh::PluginDescriptor &descriptor) {
	return pImpl->create(descriptor);
}

gumyns::sh::DeviceFactory::~DeviceFactory() {}
