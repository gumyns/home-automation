#include "Config.h"

class gumyns::sh::config::Config::Impl {
public:
    Impl(int argc, char *argv[]) {

    }

    ~Impl() {}
};


gumyns::sh::config::Config::Config(int argc, char *argv[]) : pImpl(new Impl(argc, argv)) {}

gumyns::sh::config::Config::uPtr gumyns::sh::config::Config::from(int argc, char *argv[]) {
    return uPtr(new gumyns::sh::config::Config(argc, argv));
}

std::string gumyns::sh::config::Config::restPort() {
    return "15746";
}

std::string gumyns::sh::config::Config::restNumberOfThreads() {
    return "16";
}

gumyns::sh::config::Config::~Config() {}

std::string gumyns::sh::config::Config::database() {
    return "db.sqlite";
}

std::string gumyns::sh::config::Config::zeroEndpoint() {
	return "tcp://*:12542";
}

std::string gumyns::sh::config::Config::zeroPublisher() {
	return "tcp://*:12543";
}

std::vector<std::string> gumyns::sh::config::Config::restOptions() {
    std::vector<std::string> options;
    options.push_back("num_threads");
    options.push_back(restNumberOfThreads());
    options.push_back("listening_ports");
    options.push_back(restPort());
    return options;
}

std::string gumyns::sh::config::Config::hubPluginPath() {
    return "plugins/hub";
}

std::string gumyns::sh::config::Config::devicePluginPath() {
    return "plugins/device";
}

