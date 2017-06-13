//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include <config/GPIO.h>

// ----- LED definitions ------------------------------------------------------

// Adjust these definitions for your own board.

// STM32F0DISCOVERY definitions (GREEN led, C9, active high)
// (SEGGER J-Link device name: STM32F051R8).

// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
#define BLINK_PORT_NUMBER               (0)
#define BLINK_ACTIVE_LOW                (0)

#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHBPeriph_GPIOA << (_N))
// ----------------------------------------------------------------------------

class BlinkLed
{
public:
  BlinkLed() {};

  inline static void __attribute__((always_inline))  turnOn() {
	  GPIO::A::set(GPIO::A::DIODE);
  }

  inline static void __attribute__((always_inline)) turnOff() {
	  GPIO::A::reset(GPIO::A::DIODE);
  }
};

// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
