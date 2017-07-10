#ifndef ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
#define ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H

#include <cstdint>
#include <stm32f0xx_hal.h>
#include <hub/Socket.h>

class Application {
    ha::Socket socket;
public:
    Application();
    void init();
    void run();
    void onError();
    void onExternalInterrupt(uint16_t pin);
    void onTx();
    void onRx();
};

#endif //ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
