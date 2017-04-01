#ifndef GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
#define GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H

#include <hub/Plugin.h>
#include "Connector.h"

class Parser: public gumyns::sh::plugin::hub::Parser {
	std::unique_ptr<Connector> connector;

	std::vector<uint8_t> buffer;

	gumyns::sh::plugin::hub::Parser::FrameListener listener;
public:
	Parser(nlohmann::json &);

	void write(uint32_t, std::vector<uint8_t>) override;

	void identify(uint32_t) override;

	void readListener(FrameListener) override;

	uint32_t type() override;

	~Parser() override;
};

#endif //GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
