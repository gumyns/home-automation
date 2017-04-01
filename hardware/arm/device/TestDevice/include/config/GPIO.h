#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H

#include <stm32f0xx.h>
#include "enum_utils.h"

class GPIO {
public:
	class PIN;
	class AF;
	class PinBase {
	public:
		static inline void MODER(GPIO_TypeDef * GPIO, uint32_t value, uint32_t reset) { GPIO->MODER = (GPIO->MODER & reset) | value; }
		static inline void OTYPER(GPIO_TypeDef * GPIO, uint16_t value, uint32_t reset) { GPIO->OTYPER = (GPIO->OTYPER & reset) | value; }
		static inline void OSPEEDR(GPIO_TypeDef * GPIO, uint32_t value, uint32_t reset) { GPIO->OSPEEDR = (GPIO->OSPEEDR & reset) | value; }
		static inline void PUPDR(GPIO_TypeDef * GPIO, uint32_t value, uint32_t reset) { GPIO->PUPDR = (GPIO->PUPDR & reset) | value; }
		static inline void AFRL(GPIO_TypeDef * GPIO, uint32_t value, uint32_t reset) { GPIO->AFR[0] = (GPIO->AFR[0] & reset) | value; }
		static inline void AFRH(GPIO_TypeDef * GPIO, uint32_t value, uint32_t reset) { GPIO->AFR[1] = (GPIO->AFR[1] & reset) | value; }

		static inline void setup(GPIO_TypeDef * GPIO, PIN pin) {
			MODER(GPIO, pin.mode, pin.nmode);
			OTYPER(GPIO, pin.otype, pin.notype);
			OSPEEDR(GPIO, pin.speed, pin.nspeed);
			PUPDR(GPIO, pin.resistor, pin.nresistor);
		}

		static inline void setup(GPIO_TypeDef * GPIO, AF af) {
			AFRL(GPIO, af.vl, af.nvl);
			AFRH(GPIO, af.vh, af.nvh);
		}
	};
	class PIN {
	public:
		enum Mode { IN = 0b00, OUT = 0b01, AF = 0b10, ANALOG = 0b11};
		enum OType { PUSH_PULL = 0b0, OPEN_DRAIN = 0b1};
		enum Speed { LOW = 0b00, MEDIUM = 0b01, HIGH = 0b11 };
		enum Resistor { NONE = 0b00, PULL_UP = 0b01, PULL_DOWN = 0b10 };
	private:
		constexpr static uint32_t _mode(uint16_t pin, Mode mode) { return mode << 2 * pin; };
		constexpr static uint16_t _otype(uint16_t pin, OType type) { return type << pin; };
		constexpr static uint32_t _speed(uint16_t pin, Speed speed) { return speed << 2 * pin; };
		constexpr static uint32_t _resistor(uint16_t pin, Resistor res) { return res << 2 * pin; };
	public:
		uint32_t mode, nmode;
		uint32_t otype, notype;
		uint32_t speed, nspeed;
		uint32_t resistor, nresistor;

		constexpr PIN(uint16_t pin, Mode mode, OType otype, Speed speed, Resistor resistor)
			: mode(_mode(pin, mode)), nmode(~(0b11 << 2 * pin)),
			  otype(_otype(pin, otype)), notype(~(0b1 << pin)),
			  speed(_speed(pin, speed)), nspeed(~(0b11 << 2 * pin)),
			  resistor(_resistor(pin, resistor)), nresistor(~(0b11 << 2 * pin)) {}

		constexpr PIN(uint32_t mode, uint32_t nmode, uint32_t otype, uint32_t notype,
				uint32_t speed, uint32_t nspeed, uint32_t resistor, uint32_t nresistor)
			: mode(mode), nmode(nmode),
			  otype(otype), notype(notype),
			  speed(speed), nspeed(nspeed),
			  resistor(resistor), nresistor(nresistor) {}

		constexpr static PIN merge(const PIN lhs, const PIN rhs) {
			return {lhs.mode | rhs.mode, lhs.nmode & rhs.nmode,
				lhs.otype | rhs.otype, lhs.notype & rhs.notype,
				lhs.speed | rhs.speed, lhs.nspeed & rhs.nspeed ,
				lhs.resistor | rhs.resistor, lhs.nresistor & rhs.nresistor
			};
		}
	};

	class AF {
	public:
		enum AlternativeLow { SPI_1 = 0b000 };
		enum AlternativeHigh { USART_1 = 0b0001 };
	private:
		constexpr static uint32_t _af(uint16_t pin, AlternativeLow af) { return af << 4 * (pin % 8); };
		constexpr static uint32_t _af(uint16_t pin, AlternativeHigh af) { return af << 4 * (pin % 8); };
	public:
		uint32_t vh, nvh, vl, nvl;

		constexpr AF(uint16_t pin, AlternativeLow af) : vh(0), nvh(0), vl(_af(pin, af)), nvl(~(0b1111 << 4 * (pin % 8)))  {}
		constexpr AF(uint16_t pin, AlternativeHigh af) : vh(_af(pin, af)), nvh(~(0b1111 << 4 * (pin % 8))), vl(0), nvl(0)  {}
		constexpr AF(uint32_t vh, uint32_t nvh, uint32_t vl, uint32_t nvl) : vh(vh), nvh(nvh), vl(vl), nvl(nvl) {}

		constexpr static AF merge(const AF lhs, const AF rhs) {
			return {lhs.vh | rhs.vh, lhs.nvh & rhs.nvh, lhs.vl | rhs.vl, lhs.nvl & rhs.nvl};
		}
	};
public:
	class A: public PinBase {
	public:
		enum Pin {
			DIODE 	=	3,
			SS 		= 	4,
			SCK 	= 	5,
			MISO 	= 	6,
			NOTIFIER = 	7,
			RX 		= 	9,
			TX 		= 	10,
		};

		static inline void init() {
			PIN pin				  {DIODE, PIN::OUT, PIN::PUSH_PULL,	PIN::MEDIUM, PIN::NONE};
			pin = PIN::merge(pin, {SS, PIN::AF, PIN::PUSH_PULL,	PIN::HIGH, PIN::PULL_UP});
			pin = PIN::merge(pin, {SCK, PIN::AF, PIN::PUSH_PULL, PIN::HIGH, PIN::PULL_DOWN});
			pin = PIN::merge(pin, {MISO, PIN::AF, PIN::OPEN_DRAIN, PIN::HIGH, PIN::PULL_UP});
			pin = PIN::merge(pin, {NOTIFIER, PIN::OUT, PIN::PUSH_PULL, PIN::HIGH, PIN::NONE});
			pin = PIN::merge(pin, {RX, PIN::AF, PIN::PUSH_PULL,	PIN::HIGH, PIN::NONE});
			pin = PIN::merge(pin, {TX, PIN::AF, PIN::PUSH_PULL, PIN::HIGH, PIN::NONE});
			setup(GPIOA, pin);

			GPIO::A::reset(GPIO::A::NOTIFIER);

			AF af				{RX,	AF::USART_1};
			af = AF::merge(af, 	{TX, 	AF::USART_1});
			af = AF::merge(af, 	{SS, 	AF::SPI_1});
			af = AF::merge(af, 	{SCK, 	AF::SPI_1});
			af = AF::merge(af, 	{MISO, 	AF::SPI_1});
			setup(GPIOA, af);
		}

		constexpr static uint16_t pinMask(Pin pin) { return 1 << pin; }

		static inline void change(PIN pin) { setup(GPIOA, pin); }
		static inline void set(const Pin pin) { GPIOA->BSRR = pinMask(pin); }
		static inline void reset(const Pin pin) { GPIOA->BRR = pinMask(pin); }
		static inline uint8_t read(const Pin pin) { return GPIOA->IDR & pinMask(pin) ? 1 : 0; }

		static inline uint16_t readPort(const uint16_t mask){ return GPIOA->IDR & mask; }
		static inline void writePort(const uint16_t value, const uint16_t mask) {GPIOA->ODR = (GPIOA->ODR & ~mask) | (value & mask); };
	};

	class B {

	};
private:
	static inline void priv() {

	}
public:
	static inline void init() {
		A::init();
	}
};

#endif
