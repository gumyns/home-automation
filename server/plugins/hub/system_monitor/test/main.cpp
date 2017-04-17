#include <memory>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <hub/Plugin.h>
#include <common.h>
#include <generated/PluginDescription.h>

using namespace std;

int main() {
    boost::filesystem::path path("../plugins/hub");
 	auto factory = boost::dll::import<gumyns::sh::plugin::hub::ParserFactory>(
            path / std::string(".").append(PluginDescription::NAME).c_str(), "pHub", boost::dll::load_mode::append_decorations
 	);

	nlohmann::json json = {{}};

	try {
		auto parser = factory->create(json);

		parser->readListener([](uint32_t addr, std::vector<uint8_t> frame) {
			auto it = frame.begin();
			while (it != frame.end())
				std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(*it++) << ' ';
			std::cout << std::endl;
		});

		parser->identify(0);
		// Read all channels from specific device
		parser->write(0, {Desctiptor::read(0x00)});
		// Read specific channel from specific device
		parser->write(0, {Desctiptor::read(0x00), 0x00});
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
