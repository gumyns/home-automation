#include <hub/Socket.h>

void ha::Socket::setListener(Listener listener) {
    this->listener = listener;
}

void ha::Socket::onACK(uint8_t value) {
    if (!value) {
        if (isRunning) {
            HAL_UART_DeInit((UART_HandleTypeDef *) uart);
        } else {
            rxSize = 0;
            txSize = 0;
            if (rxBuffer != nullptr)
                delete rxBuffer;
            if (txBuffer != nullptr)
                delete txBuffer;
            HAL_UART_Init((UART_HandleTypeDef *) uart);
            HAL_UART_Receive_IT((UART_HandleTypeDef *) uart, &rxSize, 1);
        }
        isRunning = ~isRunning;
    }
}

void ha::Socket::onTx() {

}

void ha::Socket::onRx() {
    if (HAL_GPIO_ReadPin(STATUS_DIODE_GPIO_Port, STATUS_DIODE_Pin) == GPIO_PIN_RESET)
        HAL_GPIO_WritePin(STATUS_DIODE_GPIO_Port, STATUS_DIODE_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(STATUS_DIODE_GPIO_Port, STATUS_DIODE_Pin, GPIO_PIN_RESET);
}