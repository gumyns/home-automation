#ifndef ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
#define ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H

#include <cstdint>

class Application {

public:
    void init();
    void run();
    void onError(char *file, int line);
    void onExternalInterrupt(uint16_t pin);
};

#endif //ARM_DEVICE_WINDOW_SENSOR_APPLICATION_H
