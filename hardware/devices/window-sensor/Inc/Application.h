#ifndef ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
#define ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H

#include <cstdint>
#include <device/I2CSocket.h>

class Application {
    ha::I2CSocket socket;
public:
    void init();
    void run();
    void onError();
    void onExternalInterrupt(uint16_t pin);
};

#endif //ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
