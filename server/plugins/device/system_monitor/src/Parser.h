#ifndef GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
#define GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H

#include <device/Plugin.h>

class Parser: public gumyns::sh::plugin::device::Parser {
	class Impl;
	std::unique_ptr<Impl> pImpl;
public:
	Parser(nlohmann::json &);

	uint32_t type() override;

	nlohmann::json parseOutput(std::vector<uint8_t> &vector) override;

	std::vector<uint8_t> parseInput(uint8_t, nlohmann::json &json) override;

	~Parser() override;
};

#endif //GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
