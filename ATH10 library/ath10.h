#ifndef ATH10_H
#define ATH10_H

#include "ath10_config.h"

// Initialize the ATH10 sensor
void ATH10_init(void);

// Read temperature and humidity from the ATH10 sensor
void ATH10_read(float *temp, float *hum);
float ATH10_read_temperature(void);
float ATH10_read_humidity(void);
uint8_t ATH10_read_8bit_reg(uint8_t reg);
#endif
