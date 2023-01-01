#include "ath10.h"
#include "i2c.h"
#include "ath10_config.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include"ath10_i2c.h"
// ATH10 commands
#define ATH10_CMD_SOFT_RESET      0xFE

// ATH10 measurement resolution
#define ATH10_RES_HUMIDITY        0.0019073486328125
#define ATH10_RES_TEMP            0.0026812744140625
//void ATH10_write_8bit_reg(uint8_t reg, uint8_t value);
void ATH10_write_8bit_reg(uint8_t reg, uint8_t value) {
  // Write the register address and the value to the I2C bus
  ATH10_I2C_write(ATH10_I2C_ADDRESS, &reg, 1);
  ATH10_I2C_write(ATH10_I2C_ADDRESS, &value, 1);
}

/*uint16_t ATH10_read_16bit_reg(uint8_t reg) {
  uint16_t data;

  // Perform the I2C read operation to read the 16-bit register value
  ATH10_I2C_start();
  //I2C_write(ATH10_I2C_ADDRESS);
  ATH10_I2C_write_ack(ATH10_I2C_ADDRESS);
  ATH10_I2C_write_ack(reg);
  ATH10_I2C_start();
  ATH10_I2C_write(ATH10_I2C_ADDRESS | 0x01);
  data = (I2C_read() << 8) | I2C_read();
  ATH10_I2C_stop();

  return data;
}*/
uint16_t ATH10_read_16bit_reg(uint8_t reg) {
 //uint16_t data;
  uint16_t data = 0;
  // Perform the I2C read operation to read the 16-bit register value
  ATH10_I2C_start();
  uint8_t reg_addr = reg;
  ATH10_I2C_write(ATH10_I2C_ADDRESS, &reg_addr, 1);  // Write the register address to the I2C bus
  ATH10_I2C_start();
  //ATH10_I2C_write(ATH10_I2C_ADDRESS | 0x01, &data, 2);  // Read the 16-bit value from the I2C bus
  ATH10_I2C_write(ATH10_I2C_ADDRESS, &reg, 1);

  ATH10_I2C_stop();

  return data;
}

uint8_t ATH10_read_8bit_reg(uint8_t reg) {
// Write the register address to the I2C bus
ATH10_I2C_write(ATH10_I2C_ADDRESS, &reg, 1);

// Read the 8-bit value from the I2C bus
uint8_t data;
ATH10_I2C_read(ATH10_I2C_ADDRESS, &data, 1);


return data;
}

void ATH10_init(void) {
  // Initialize the I2C communication
  ATH10_init();

  // Check the device ID to make sure the sensor is connected
  uint8_t device_id = ATH10_read_8bit_reg(ATH10_REG_DEVICE_ID);
  if (device_id != ATH10_DEVICE_ID) {
    // Print an error message if the device ID is incorrect
    printf("Error: ATH10 sensor not found\n");
    return;
  }

  // Set the control register to the default value
  ATH10_write_8bit_reg(ATH10_REG_CONTROL, ATH10_CONTROL_DEFAULT);
}

float ATH10_read_humidity(void) {
// Declare variables to store the raw humidity value and the final humidity value
uint16_t humidity_raw;
float humidity;

// Read the raw humidity value from the ATH10 sensor
humidity_raw = ATH10_read_16bit_reg(ATH10_RES_HUMIDITY);

// Convert the raw humidity value to a floating point value in the range 0-100
humidity = humidity_raw * ATH10_RESOLUTION_HUM;

return humidity;
}

float ATH10_read_temperature(void) {
// Declare variables to store the raw temperature value and the final temperature value
uint16_t temp_raw;
float temperature;


// Read the raw temperature value from the ATH10 sensor
temp_raw = ATH10_read_16bit_reg(ATH10_REG_TEMP_MSB);

// Convert the raw temperature value to a floating point value in Celsius
temperature = temp_raw * ATH10_RESOLUTION_TEMP;

return temperature;
}
