#ifndef ATH10_I2C_H
#define ATH10_I2C_H

#include "stm32f4xx_hal.h"
#include "ath10.h"
#include "i2c.h"
#include "ath10_config.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
// I2C SDA and SCL pins
#define I2C_SDA_GPIO_Port GPIOC
#define I2C_SDA_Pin       GPIO_PIN_9
#define I2C_SCL_GPIO_Port GPIOC
#define I2C_SCL_Pin       GPIO_PIN_8

// I2C clock frequency
#define I2C_CLOCK_FREQ    400000

// I2C timeout
#define I2C_TIMEOUT       1000

// I2C address of the ATH10 sensor
#define ATH10_I2C_ADDRESS 0x40

// Function prototypes
uint8_t ATH10_I2C_read_ack(uint8_t ack);
void ATH10_I2C_write_ack(uint8_t data);
void ATH10_I2C_init(void);
void ATH10_I2C_start(void);
void ATH10_I2C_stop(void);
void ATH10_I2C_write(uint8_t address, uint8_t *data, uint8_t length);
void ATH10_I2C_read(uint8_t address, uint8_t *data, uint8_t length);
//void ATH10_I2C_write(uint8_t data);
//uint8_t ATH10_I2C_read(uint8_t ack);
#endif // ATH10_I2C_H
