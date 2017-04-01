#include <iostream>
#include "Factory.h"
#include "Parser.h"

gumyns::sh::plugin::device::Parser::uPtr _ParserFactory::create(nlohmann::json &json) {
	return gumyns::sh::plugin::device::Parser::uPtr(new Parser(json));
}
