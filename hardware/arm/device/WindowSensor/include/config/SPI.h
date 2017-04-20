#ifndef SPI_h_
#define SPI_H_

#include <stm32f0xx.h>
#include "enum_utils.h"

#define SPI_dataMask(bits) (bits - 1) << 8

class SPI {
private:
public:
	class ISR {
	public:
		enum _ISR {
			TXE = SPI_SR_TXE,
			RXNE = SPI_SR_RXNE
		};
		static inline bool has(_ISR interrupt) { return SPI1->SR & interrupt; }
	};
	class CR1 {
	public:
		enum _CR1 {
			MASTER = SPI_CR1_MSTR,
			SPI = SPI_CR1_SPE,
			BIDIRECTIONAL_MODE = SPI_CR1_BIDIMODE,
			BIDIRECTIONAL_OUTPUT = SPI_CR1_BIDIOE,
			PRESCALLER_256 = SPI_CR1_BR
		};
		static inline void enable(_CR1 IT) { SPI1->CR1 |= IT; }
		static inline void disable(_CR1 IT) { SPI1->CR1 &= ~(IT); }
		static inline void set(_CR1 IT) { SPI1->CR1 = IT; }
		static inline void reset() { SPI1->CR1 = 0; }
	};
	class CR2 {
	public:
		enum _CR2 {
			TXE = SPI_CR2_TXEIE,
			RXNE = SPI_CR2_RXNEIE,
			FIFO_THRESHOLD = SPI_CR2_FRXTH,
			SS_PULSE = SPI_CR2_NSSP,
			SS_HARDWARE = SPI_CR2_SSOE,
			DATA_8_BIT = SPI_dataMask(9)
		};
		static inline void enable(_CR2 IT) { SPI1->CR2 |= IT; }
		static inline void disable(_CR2 IT) { SPI1->CR2 &= ~(IT); }
		static inline void set(_CR2 IT) { SPI1->CR2 = IT; }
		static inline void reset() { SPI1->CR2 = 0; }
	};
	class I2S {
	public:
		static inline void reset() { SPI1->I2SCFGR = 0; }
	};


	static inline void write(uint8_t data) { SPI1->DR = 0x0FF & data; } // TODO
	static inline uint16_t read() { return SPI1->DR; }
};

__enum__or__operator__(SPI::ISR::_ISR);
__enum__or__operator__(SPI::CR1::_CR1)
__enum__or__operator__(SPI::CR2::_CR2)

#undef SPI_dataMask

#endif
