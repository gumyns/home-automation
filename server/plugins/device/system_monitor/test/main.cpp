#include <memory>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <device/Plugin.h>
#include <common.h>
#include <generated/PluginDescription.h>

void parseTo(gumyns::sh::plugin::device::Parser* parser, uint8_t descriptor, nlohmann::json json) {
	std::cout << "From: " << json << " -> " << toHexString(parser->parseInput(descriptor, json)) << std::endl;
}

void parseFrom(gumyns::sh::plugin::device::Parser* parser, std::vector<uint8_t> frame) {
	std::cout << "From: " << toHexString(frame) << " -> " << parser->parseOutput(frame) << std::endl;
}

int main() {
    boost::filesystem::path path("../plugins/device");
 	auto factory = boost::dll::import<gumyns::sh::plugin::device::ParserFactory>(
            path / std::string(".").append(PluginDescription::NAME).c_str(), "pDevice", boost::dll::load_mode::append_decorations
 	);

	// This is how a valid requests looks like
	// {"address":1, "r":[]}
	// {"address":1, "r":["value"]}
	// {"address":1, "w":[{"value":42}]}

	nlohmann::json readAll = 				nlohmann::json::parse("{\"r\":[]}");
	nlohmann::json readSingle = 			nlohmann::json::parse("{\"r\":[\"temperature\"]}");
	nlohmann::json writeSingle = 			nlohmann::json::parse("{\"w\":[{\"temperature\":42}]}");

	nlohmann::json json{{}};

	auto parser = factory->create(json);

	parseTo(parser.get(), 0, readAll);
	parseTo(parser.get(), 0, readSingle);
	parseTo(parser.get(), 0, writeSingle);

	parseFrom(parser.get(), {0x01 << 5, 0x01, 0x01, 0x01}); // should be empty !
	parseFrom(parser.get(), {0x60, 0x00, 0xcb, 0x20});

	return 0;
}
