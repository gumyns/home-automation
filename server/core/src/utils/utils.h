#ifndef GUMYNS_SMART_HOME_PIMPL_H
#define GUMYNS_SMART_HOME_PIMPL_H

#include <memory>

#define POINTERS(classname) public:\
						typedef std::shared_ptr<classname> sPtr; \
						typedef std::weak_ptr<classname> wPtr; \
						typedef std::unique_ptr<classname> uPtr; \
						private: \

#define PIMPL(classname) POINTERS(classname) \
						class Impl;	\
						std::unique_ptr<Impl> pImpl; \
						classname(const classname &copy) = delete;

#define ZERO_BUFFER(name, size) uint8_t name[size]; \
								memset(name, 0, size);

#define COPY_REQUEST(output, input, offset) memcpy(&output[0], &static_cast<uint8_t *>(input.data())[offset], input.size() - offset);

#define json_create_and_parse(var, src) nlohmann::json var; \
	try { \
		var = nlohmann::json::parse((char *)src); \
	} catch (...) { \
		LogE << "SafeJson failed: " << (char *)src; \
	}

#endif //GUMYNS_SMART_HOME_PIMPL_H
