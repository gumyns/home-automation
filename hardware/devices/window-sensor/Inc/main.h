#ifndef __MAIN_H
#define __MAIN_H

#include <I2CAddresses.h>

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
