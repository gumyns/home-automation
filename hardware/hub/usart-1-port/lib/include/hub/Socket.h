#ifndef ARM_DEVICE_WINDOW_SENSOR_SOCKET_H
#define ARM_DEVICE_WINDOW_SENSOR_SOCKET_H

#include <stm32f0xx_hal.h>
#include <functional>

namespace ha {
    class Socket {
    public:
        /** Byte listener, should be called in IRQ handler implementation */
        typedef std::function<void(uint8_t)> Listener;
    private:
        UART_HandleTypeDef const *uart;
        uint8_t isRunning = 0;
        uint8_t rxSize = 0, txSize = 0;
        uint8_t *rxBuffer;
        uint8_t *txBuffer;
        Listener listener;
    public:
        Socket(UART_HandleTypeDef *uart): uart(uart) {};
        void setListener(Listener listener);
        void onACK(uint8_t value);
        void onRx();
        void onTx();
    };
}

#endif //ARM_DEVICE_WINDOW_SENSOR_SOCKET_H
