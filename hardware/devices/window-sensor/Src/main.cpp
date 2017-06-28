#include <Application.h>
#include "main.h"

Application app;

int main(void) {
    app.init();
    app.run();
}

void _Error_Handler(char *file, int line) {
    app.onError(file, line);
}

void HAL_GPIO_EXTI_Callback(uint16_t pin) {
    app.onExternalInterrupt(pin);
}