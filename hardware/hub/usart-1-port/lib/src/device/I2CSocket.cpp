#include "../../include/device/I2CSocket.h"

void ha::I2CSocket::setListener(Listener listener) {
    this->listener = listener;
}
