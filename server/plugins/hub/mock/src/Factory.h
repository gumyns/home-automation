#ifndef PLUGIN_H
#define PLUGIN_H

#include <hub/Plugin.h>
#include <boost/config.hpp>

class _ParserFactory : public gumyns::sh::plugin::hub::ParserFactory {
public:
	_ParserFactory() = default;

	std::unique_ptr<gumyns::sh::plugin::hub::Parser> create(nlohmann::json &json) override;

	~_ParserFactory() {};
};

extern "C" BOOST_SYMBOL_EXPORT _ParserFactory Plugin;
_ParserFactory Plugin;

#endif //PLUGIN_H
