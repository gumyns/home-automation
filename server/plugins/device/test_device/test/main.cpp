#include <memory>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <device/Plugin.h>
#include <utils.h>

void parseTo(gumyns::sh::plugin::device::Parser* parser, uint8_t address, nlohmann::json json) {
	std::cout << "From: " << json << " -> " << toHexString(parser->parseInput(address, json)) << std::endl;
}

void parseFrom(gumyns::sh::plugin::device::Parser* parser, std::vector<uint8_t> frame) {
	std::cout << "From: " << toHexString(frame) << " -> " << parser->parseOutput(frame) << std::endl;
}

int main() {
	boost::filesystem::path path("../lib");
 	auto factory = boost::dll::import<gumyns::sh::plugin::device::ParserFactory>(
 		path / "TestDevice", "pDevice", boost::dll::load_mode::append_decorations
 	);

	// This is how a valid requests looks like
	// {"address":1, "r":[]}
	// {"address":1, "r":["status"]}
	// {"address":1, "r":["status", "temperature"]}
	// {"address":1, "w":[{"status":true}, {"temperature":42.52}]}

	nlohmann::json readAll = 				nlohmann::json::parse("{\"r\":[]}");
	nlohmann::json readSingle = 			nlohmann::json::parse("{\"r\":[\"status\"]}");
	nlohmann::json readMultiple = 			nlohmann::json::parse("{\"r\":[\"status\", \"temperature\"]}");
	nlohmann::json readMultipleNonExisting =nlohmann::json::parse("{\"r\":[\"status\", \"temperature\", \"not_here\"]}");
	nlohmann::json writeSingle = 			nlohmann::json::parse("{\"w\":[{\"status\":true}]}");
	nlohmann::json writeSingleFalse = 		nlohmann::json::parse("{\"w\":[{\"status\":false}]}");
	nlohmann::json write = 					nlohmann::json::parse("{\"w\":[{\"status\":true}, {\"temperature\":12.5}]}");
	nlohmann::json write2 = 				nlohmann::json::parse("{\"w\":[{\"status\":false}, {\"temperature\":62}]}");

	nlohmann::json json{{}};

	auto parser = factory->create(json);

	parseTo(parser.get(), 0, readAll);
	parseTo(parser.get(), 0, readSingle);
	parseTo(parser.get(), 0, readMultiple);
	parseTo(parser.get(), 0, readMultipleNonExisting);
	parseTo(parser.get(), 0, writeSingle);
	parseTo(parser.get(), 0, writeSingleFalse);
	parseTo(parser.get(), 0, write);
	parseTo(parser.get(), 0, write2);

	parseFrom(parser.get(), {0x00, 0x01, 0x01, 0x01}); // should be empty !
	parseFrom(parser.get(), {0x03 << 5, 0x00, 0x00});
	parseFrom(parser.get(), {0x03 << 5, 0x00, 0x01});

	return 0;
}
