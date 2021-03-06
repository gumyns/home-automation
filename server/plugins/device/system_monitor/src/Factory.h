#ifndef PLUGIN_H
#define PLUGIN_H

#include <device/Plugin.h>
#include <boost/config.hpp>

class _ParserFactory : public gumyns::sh::plugin::device::ParserFactory {
public:
	_ParserFactory() = default;

	gumyns::sh::plugin::device::Parser::uPtr create(nlohmann::json &json) override;

	~_ParserFactory() {};
};

extern "C" BOOST_SYMBOL_EXPORT _ParserFactory pDevice;
_ParserFactory pDevice;

#endif //PLUGIN_H
