#ifndef ARM_DEVICE_WINDOW_SENSOR_I2CADDRESSES_H
#define ARM_DEVICE_WINDOW_SENSOR_I2CADDRESSES_H

/** Master aka hub address, there can be only one hub in sub network */
#define I2C_ADDR_MASTER 8

/** Address of specific device provided via build parameter, otherwise device address will be 0, ok for testing */
#ifndef I2C_ADDRESS
#define I2C_ADDRESS 0
#endif

/** Validate device address and fail build if not valid */
#if (I2C_ADDRESS >= 0 && I2C_ADDRESS <= 63)
#define I2C_ADDR I2C_ADDRESS + I2C_ADDR_MASTER + 1
#endif

#endif //ARM_DEVICE_WINDOW_SENSOR_I2CADDRESSES_H
