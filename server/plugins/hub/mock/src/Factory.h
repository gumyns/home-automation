#ifndef PLUGIN_H
#define PLUGIN_H

#include <hub/Plugin.h>
#include <boost/config.hpp>

class _ParserFactory : public gumyns::sh::plugin::hub::ParserFactory {
public:
	_ParserFactory() = default;

	gumyns::sh::plugin::hub::Parser::uPtr create(nlohmann::json &json) override;

	~_ParserFactory() {};
};

extern "C" BOOST_SYMBOL_EXPORT _ParserFactory pHub;
_ParserFactory pHub;

#endif //PLUGIN_H
