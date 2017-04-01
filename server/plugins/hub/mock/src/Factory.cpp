#include <iostream>
#include "Factory.h"
#include "Parser.h"

std::unique_ptr<gumyns::sh::plugin::hub::Parser> _ParserFactory::create(nlohmann::json &json) {
	return std::unique_ptr<gumyns::sh::plugin::hub::Parser>(new Parser(json));
}
