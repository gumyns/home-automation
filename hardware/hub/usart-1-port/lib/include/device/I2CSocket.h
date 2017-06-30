#ifndef ARM_DEVICE_WINDOW_SENSOR_I2CSOCKET_H
#define ARM_DEVICE_WINDOW_SENSOR_I2CSOCKET_H

#include <functional>

namespace ha {
    class I2CSocket {
    public:
        /** Byte listener, should be called in IRQ handler implementation */
        typedef std::function<void(uint8_t)> Listener;
    private:
        Listener listener;
    public:
        void setListener(Listener listener);
    };
}

#endif //ARM_DEVICE_WINDOW_SENSOR_I2CSOCKET_H
