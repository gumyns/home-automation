#ifndef CONFIG_H_
#define CONFIG_H_

#include "Clock.h"
#include "GPIO.h"

namespace Config {
	static inline void init() {
		Clock::init();
		GPIO::init();
	}
}

#endif /* CONFIG_H_ */
