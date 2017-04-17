#include <iostream>
#include "Factory.h"
#include "Parser.h"

gumyns::sh::plugin::hub::Parser::uPtr _ParserFactory::create(nlohmann::json &json) {
	return gumyns::sh::plugin::hub::Parser::uPtr(new Parser(json));
}
