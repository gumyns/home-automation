#ifndef GUMYNS_SMART_HOME_PLUGIN_DEVICE_COMMON_H
#define GUMYNS_SMART_HOME_PLUGIN_DEVICE_COMMON_H

static std::string toHexString(std::vector<uint8_t> vector) {
	std::stringstream builder;
	auto it = vector.begin();
	builder << "[ ";
	while (it != vector.end())
		builder << std::hex << std::setfill('0') << std::setw(2) << (int)*it++ << " ";
	builder << "]";
	return builder.str();
}

static void appendVector(std::vector<uint8_t> &dest, std::vector<uint8_t> src) {
	dest.insert(dest.end(), src.begin(), src.end());
}

static std::vector<uint8_t> createChunk(uint8_t channel, std::vector<uint8_t> &dest, std::vector<uint8_t> src) {
	dest.push_back(channel);
	dest.insert(dest.end(), src.begin(), src.end());
	return dest;
}

struct Desctiptor {
	enum Order { IDENTIFY = 0x00, READ = 0x01, WRITE = 0x02, RESPONSE = 0x03 };

	static inline uint8_t identify() { return (uint8_t)(IDENTIFY << 5); }
	static inline uint8_t read(uint8_t address) { return (uint8_t)(READ << 5 | address); }
	static inline uint8_t write(uint8_t address) { return (uint8_t)(WRITE << 5 | address); }
	static inline uint8_t response(uint8_t address) { return (uint8_t)(RESPONSE << 5 | address); }

	static inline uint8_t address(uint8_t descriptor) {
		return (uint8_t) (descriptor & 0x1F);
	}

	static inline Order order(uint8_t descriptor) {
		return (Order)(descriptor >> 5);
	}
};

struct Chunk {
	static std::vector<uint8_t> create(uint8_t channel, std::vector<uint8_t> src) {
		std::vector<uint8_t> dest;
		dest.push_back(channel);
		dest.insert(dest.end(), src.begin(), src.end());
		return dest;
	}
};

struct Short {
	static std::vector<uint8_t> serialize(short value) {
		return {static_cast<uint8_t>((value & 0xFF00) >> 8), static_cast<uint8_t>(value & 0xFF)};
	}

	static short deserialize(std::vector<uint8_t>::iterator &it) {
		short value = 0;
		value = *it++;
		value <<= 8;
		value += *it++;
		return value;
	}
};

#endif //GUMYNS_SMART_HOME_PLUGIN_DEVICE_COMMON_H
