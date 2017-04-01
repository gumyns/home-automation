#ifndef USART_H_
#define USART_H_

#include <stm32f0xx.h>
#include "enum_utils.h"

class Usart {
private:
	constexpr static USART_TypeDef * _USART = USART1;
public:
	class ISR {
	public:
		enum _ISR {
			TXE = USART_ISR_TXE,
			RXNE = USART_ISR_RXNE
		};
		static inline bool has(_ISR interrupt) { return _USART->ISR & interrupt; }
	};
	class CR1 {
	public:
		enum _CR1 {
			TXE = USART_CR1_TXEIE,
			RXNE = USART_CR1_RXNEIE,
			USART = USART_CR1_UE
		};

		static inline void enable(_CR1 IT) { _USART->CR1 |= IT; }
		static inline void disable(_CR1 IT) { _USART->CR1 &= ~(IT); }
		static inline void reset() { _USART->CR1 = 0; }
	};

	static inline void write(uint8_t data) { _USART->TDR = data; }
	static inline uint8_t read() { return _USART->RDR; }
};

__enum__or__operator__(Usart::ISR::_ISR)
__enum__or__operator__(Usart::CR1::_CR1)

#endif
