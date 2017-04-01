#include <cstring>
#include <utils/Logger.h>
#include  <iostream>
#include  <iomanip>
#include "BindingManager.h"
#include "Bimap.h"


class gumyns::sh::BindingManager::Impl {
	/*! Bimap for <address, binding> */
	Bimap bimap;
public:
	Impl(){}

	~Impl(){}

	std::string toHex(uint64_t value) {
		std::stringstream builder;
		builder << std::hex << std::setfill('0') << std::setw(12) << value;
		std::stringstream ret;
		ret << builder.str().substr(0, 4) << "." << builder.str().substr(4, 4) << "." << builder.str().substr(8, 4);
		return ret.str();
	}

	uint64_t add(const uint8_t *frame, size_t size) {
		uint64_t addr = 0;
		for (int i = 0; i < 6; i++) addr = (addr << 8) + (int)frame[i];
		char binding[size - 5];  // -5 not -6, because of trailing \0
		memset(binding, 0, size - 5);
		memcpy(binding, &frame[6], size - 6);
		std::string bind(binding);
		LogD << "Binding add: " << toHex(addr) << ", " << binding << std::endl;
		bimap.insert(bind, addr);
		return addr;
	}

	std::string byAddress(uint64_t address) {
		return bimap.get(address);
	}

	uint64_t byBinding(std::string &binding) {
		return bimap.get(binding);
	}

};
gumyns::sh::BindingManager::BindingManager() : pImpl(new gumyns::sh::BindingManager::Impl()) {}

gumyns::sh::BindingManager::~BindingManager() {}

uint64_t gumyns::sh::BindingManager::add(const uint8_t *frame, size_t size) {
	return pImpl->add(frame, size);
}

std::string gumyns::sh::BindingManager::byAddress(uint64_t address) {
	return pImpl->byAddress(address);
}

uint64_t gumyns::sh::BindingManager::byBinding(std::string &binding) {
	return pImpl->byBinding(binding);
}



