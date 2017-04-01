#ifndef GUMYNS_SMART_HOME_LOGGER_H
#define GUMYNS_SMART_HOME_LOGGER_H

//#include <boost/log/trivial.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//#define LogD BOOST_LOG_TRIVIAL(debug) << __FILENAME__ << ':' << __LINE__ << " : "
//#define LogI BOOST_LOG_TRIVIAL(info) << __FILENAME__ << ':' << __LINE__ << " : "
//#define LogE BOOST_LOG_TRIVIAL(error) << __FILENAME__ << ':' << __LINE__ << " : "

#define LogD std::cout << std::dec << __FILENAME__ << ':' << __LINE__ << " : "
#define LogI std::cout << std::dec << __FILENAME__ << ':' << __LINE__ << " : "
#define LogE std::cout << std::dec << __FILENAME__ << ':' << __LINE__ << " : "

static std::string toHexString(void * buffer, size_t size) {
	std::stringstream builder;
	builder << "[ ";
	for (int i = 0; i < size; i++) {
		builder << std::hex << std::setfill('0') << std::setw(2) << (int) static_cast<uint8_t*>(buffer)[i] << " ";
	}
	builder << "]";
	return builder.str();
}

#endif //GUMYNS_SMART_HOME_LOGGER_H
