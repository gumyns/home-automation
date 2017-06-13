#ifndef CONFIG_CLOCK_H_
#define CONFIG_CLOCK_H_

#include <stm32f0xx.h>

namespace Config {
struct Clock {
	static inline void init() {
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN | RCC_APB2ENR_SPI1EN | RCC_APB2ENR_USART1EN;
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	}
};
}
#endif
