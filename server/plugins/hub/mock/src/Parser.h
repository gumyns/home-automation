#ifndef GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
#define GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H

#include <hub/Plugin.h>

class Parser: public gumyns::sh::plugin::hub::Parser {
	class Impl;
	std::unique_ptr<Impl> pImpl;
public:
	Parser(nlohmann::json &);

	void write(uint32_t, std::vector<uint8_t>) override;

	void identify(uint32_t) override;

	void readListener(FrameListener) override;

	~Parser() override;
};

#endif //GUMYNS_SMART_HOME_PLUGIN_HUB_USART_OVER_TTY_PARSER_H
