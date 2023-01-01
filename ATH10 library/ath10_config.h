#ifndef ATH10_CONFIG_H
#define ATH10_CONFIG_H

#include <stdint.h>
#include "ath10.h"
// ATH10 I2C address
#define ATH10_I2C_ADDRESS 0x40

// ATH10 registers
#define ATH10_REG_DEVICE_ID 0xD0
#define ATH10_REG_CONTROL   0xF2
#define ATH10_REG_TEMP_MSB  0xF3
#define ATH10_REG_TEMP_LSB  0xF4
#define ATH10_REG_HUM_MSB   0xF5
#define ATH10_REG_HUM_LSB   0xF6

// ATH10 device ID
#define ATH10_DEVICE_ID 0xBC

// ATH10 control register default value
#define ATH10_CONTROL_DEFAULT 0x3A

// ATH10 measurement resolution
#define ATH10_RESOLUTION_TEMP 0.01f
#define ATH10_RESOLUTION_HUM  0.04f

#endif
