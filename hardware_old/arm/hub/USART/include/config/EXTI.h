#ifndef EXTI_H_
#define EXTI_H_

#include "GPIO.h"
#include <stm32f0xx.h>

struct Exti {
	enum Line { NOTIFIER = GPIO::A::pinMask(GPIO::A::NOTIFIER) };

	static inline uint32_t pending(Exti::Line line) { return EXTI->PR & line; }
	static inline void clear(Exti::Line line) { EXTI->PR = line; }
	static inline void initNotifier() {
		// SYSCFG->EXTICR // set this only when exti is on another port than A
		EXTI->IMR |= NOTIFIER;
		EXTI->RTSR |= NOTIFIER;
		EXTI->FTSR |= NOTIFIER;
	}
};

#endif
