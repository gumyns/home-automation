#ifndef EXTI_H_
#define EXTI_H_

#include "GPIO.h"
#include <stm32f0xx.h>

struct Exti {
	enum Line { SENSOR0 = GPIO::A::pinMask(GPIO::A::SENSOR0) };

	static inline uint32_t pending(Exti::Line line) { return EXTI->PR & line; }
	static inline void clear(Exti::Line line) { EXTI->PR = line; }
	static inline void init() {
		// SYSCFG->EXTICR // set this only when exti is on another port than A
		EXTI->IMR |= SENSOR0;
		EXTI->RTSR |= SENSOR0;
		EXTI->FTSR |= SENSOR0;
	}
};

#endif
