
#include "ath10_i2c.h"
#include "ath10.h"
#include "i2c.h"
#include "ath10_config.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdio.h>

// I2C handle
I2C_HandleTypeDef hi2c;
#define I2C_ERROR_NONE HAL_I2C_ERROR_NONE
// Initialize the I2C communication
// Initialize the I2C communication
void ATH10_I2C_init(void)
{
  // Enable the I2C clock
  __HAL_RCC_I2C1_CLK_ENABLE();

  // Configure the I2C pins
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin       = I2C_SDA_Pin | I2C_SCL_Pin;
  gpio_init.Mode      = GPIO_MODE_AF_OD;
  gpio_init.Pull      = GPIO_PULLUP;
  gpio_init.Speed     = GPIO_SPEED_FAST;
  gpio_init.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(I2C_SDA_GPIO_Port, &gpio_init);

  // Initialize the I2C handle
  hi2c.Instance             = I2C1;
  hi2c.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  hi2c.Init.ClockSpeed      = I2C_CLOCK_FREQ;
  hi2c.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  hi2c.Init.OwnAddress1     = 0;
  hi2c.Init.OwnAddress2     = 0;

  HAL_I2C_Init(&hi2c);
}
void ATH10_I2C_start(void)
{
  // Set the I2C SDA and SCL pins to low
  HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, 0);
  HAL_GPIO_WritePin(I2C_SCL_GPIO_Port, I2C_SCL_Pin, 0);
}
void ATH10_I2C_stop(void)
{

  // Set the I2C stop condition
	//HAL_I2C_Master_Abort_IT(&hi2c);
	HAL_I2C_Master_Abort_IT(&hi2c, I2C_ERROR_NONE);  // Use the correct function and pass the correct arguments
}

void ATH10_I2C_write(uint8_t address, uint8_t *data, uint8_t length)
{
// Write the data to the I2C bus
HAL_I2C_Master_Sequential_Transmit_IT(&hi2c, address, data, length, I2C_TIMEOUT);

// Wait for the I2C transaction to complete
while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);
}



void ATH10_I2C_read(uint8_t address, uint8_t *data, uint8_t length)
{
// Read data from the I2C bus
//return
		HAL_I2C_Master_Sequential_Receive_IT(&hi2c, address, data, length, I2C_TIMEOUT);
}


void ATH10_I2C_write_ack(uint8_t data)
{
// Write the data to the I2C bus
HAL_I2C_Master_Transmit(&hi2c, ATH10_I2C_ADDRESS, &data, 1, I2C_TIMEOUT);

// Wait for the I2C transaction to complete
while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);
}



uint8_t ATH10_I2C_read_ack(uint8_t ack)
{
// Read data from the I2C bus
uint8_t data;
HAL_I2C_Master_Receive(&hi2c, ATH10_I2C_ADDRESS, &data, 1, ack ? I2C_TIMEOUT : I2C_TIMEOUT);

// Wait for the I2C transaction to complete
while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);

return data;
}

/*#include "ath10_i2c.h"
#include "ath10.h"
#include "i2c.h"
#include "ath10_config.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
// I2C handle
I2C_HandleTypeDef hi2c;

// Initialize the I2C communication
void ATH10_I2C_init(void)
{
  // Enable the I2C clock
  __HAL_RCC_I2C1_CLK_ENABLE();

  // Configure the I2C pins
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin       = I2C_SDA_Pin | I2C_SCL_Pin;
  gpio_init.Mode      = GPIO_MODE_AF_OD;
  gpio_init.Pull      = GPIO_PULLUP;
  gpio_init.Speed     = GPIO_SPEED_FAST;
  gpio_init.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(I2C_SDA_GPIO_Port, &gpio_init);

  // Initialize the I2C handle
  hi2c.Instance             = I2C1;
  hi2c.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  hi2c.Init.ClockSpeed      = I2C_CLOCK_FREQ;
  hi2c.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  hi2c.Init.OwnAddress1     = 0;
  hi2c.Init.OwnAddress2     = 0;
  hi2c.Init.Timing          = 0;
  HAL_I2C_Init(&hi2c);
}

// Start the I2C communication
void ATH10_I2C_start(void)
{
  // Set the I2C SDA and SCL pins to low
  HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, 0);
  HAL_GPIO_WritePin(I2C_SCL_GPIO_Port, I2C_SCL_Pin, 0);
}
void ATH10_I2C_stop(void)
{
// Set the I2C stop condition
HAL_I2C_Master_Stop(&hi2c);
}
void ATH10_I2C_write(uint8_t address, uint8_t *data, uint8_t length)
{
  // Write the data to the I2C bus
  HAL_I2C_Master_Sequential_Transmit_IT(&hi2c, address, data, length, I2C_TIMEOUT);

  // Wait for the I2C transaction to complete
  while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);
}

uint8_t ATH10_I2C_read(uint8_t address, uint8_t *data, uint8_t length)
{
  // Read data from the I2C bus
  return HAL_I2C_Master_Sequential_Receive_IT(&hi2c, address, data, length, I2C_TIMEOUT);
}
*/
