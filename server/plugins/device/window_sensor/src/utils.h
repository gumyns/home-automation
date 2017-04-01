#ifndef GUMYNS_SMART_HOME_PLUGIN_DEVICE_TEST_DEVICE_UTILS_H
#define GUMYNS_SMART_HOME_PLUGIN_DEVICE_TEST_DEVICE_UTILS_H

static std::string toHexString(std::vector<uint8_t> vector) {
	std::stringstream builder;
	auto it = vector.begin();
	builder << "[ ";
	while (it != vector.end())
		builder << std::hex << std::setfill('0') << std::setw(2) << (int)*it++ << " ";
	builder << "]";
	return builder.str();
}

#endif //GUMYNS_SMART_HOME_PLUGIN_DEVICE_TEST_DEVICE_UTILS_H
