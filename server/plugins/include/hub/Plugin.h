#ifndef GUMYNS_SH_HUB_PLUGIN_H
#define GUMYNS_SH_HUB_PLUGIN_H

#include <memory>
#include <vector>
#include <json.hpp>

namespace gumyns {
namespace sh {
namespace plugin {
namespace hub {

	class Parser {
	public:
		typedef std::unique_ptr<Parser> uPtr;
		typedef std::function<void(uint32_t, std::vector<uint8_t>)> FrameListener;

		virtual uint32_t type() = 0;

		virtual void write(uint32_t, std::vector<uint8_t>) = 0;

		virtual void identify(uint32_t) = 0;

		virtual void readListener(FrameListener) = 0;

		virtual ~Parser() {}
	};

	class ParserFactory {
	public:
		virtual Parser::uPtr create(nlohmann::json &) = 0;

		virtual ~ParserFactory() {}
	};
}}}}

#endif // GUMYNS_SH_HUB_PLUGIN_H
