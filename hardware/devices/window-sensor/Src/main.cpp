#include <Application.h>
#include "stm32f0xx_hal.h"
#include "main.h"

Application app;

int main(void) {
    app.init();
    app.run();
    return 0;
}

void _Error_Handler() {
    app.onError();
}

void HAL_GPIO_EXTI_Callback(uint16_t pin) {
    app.onExternalInterrupt(pin);
}
