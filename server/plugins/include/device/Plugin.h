#ifndef GUMYNS_SH_DEVICE_PLUGIN_H
#define GUMYNS_SH_DEVICE_PLUGIN_H

#include <memory>
#include <vector>
#include <json.hpp>


namespace gumyns {
namespace sh {
namespace plugin {
namespace device {

	class Parser {
	public:
		typedef std::unique_ptr<Parser> uPtr;
		typedef std::shared_ptr<Parser> sPtr;
		typedef std::weak_ptr<Parser> wPtr;

		virtual uint32_t type() = 0;

		virtual nlohmann::json parseOutput(std::vector<uint8_t> &) = 0;

		virtual std::vector<uint8_t> parseInput(uint8_t, nlohmann::json &) = 0;

		virtual ~Parser() {}
	};

	class ParserFactory {
	public:
		virtual Parser::uPtr create(nlohmann::json &) = 0;

		virtual ~ParserFactory() {}
	};

}}}}

#endif // GUMYNS_SH_DEVICE_PLUGIN_H
