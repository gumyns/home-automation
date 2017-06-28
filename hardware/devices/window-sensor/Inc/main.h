#ifndef __MAIN_H
#define __MAIN_H

#include "../lib/common/I2CAddresses.h"

#define INT_Pin GPIO_PIN_13
#define INT_GPIO_Port GPIOA
#define INT_EXTI_IRQn EXTI4_15_IRQn
#define STATUS_DIODE_Pin GPIO_PIN_14
#define STATUS_DIODE_GPIO_Port GPIOA

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
