#ifndef SMARTHOMESERVER_CONFIG_H
#define SMARTHOMESERVER_CONFIG_H

#include <string>
#include <utils/utils.h>
#include <vector>


namespace gumyns {
namespace sh {
namespace config {

    class Config {
		PIMPL(Config);

        Config(int, char **);
    public:
        ~Config();

        static uPtr from(int, char *[]);

        std::string database();

        std::vector<std::string> restOptions();

        std::string restPort();

        std::string restNumberOfThreads();

		std::string zeroEndpoint();

        std::string zeroPublisher();

		std::string hubPluginPath();

		std::string devicePluginPath();
    };

}}}

#endif //SMARTHOMESERVER_CONFIG_H
