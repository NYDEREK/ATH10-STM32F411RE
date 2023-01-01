ATH10 Humidity and Temperature Sensor Library This library provides functions for interacting with the ATH10 humidity and temperature sensor using I2C communication. The library was developed and tested on a STM32F4 microcontroller, but it should also work on other microcontrollers with slight modifications.

Usage To use the library, include ath10.h in your project and call the ATH10_init() function to initialize the sensor. Then, you can use the following functions to read the humidity and temperature:

Copy code float ATH10_read_temperature(); // returns temperature in Celsius float ATH10_read_humidity(); // returns relative humidity in percentage Limitations Note that the ATH10 sensor has a resolution of 0.1% for humidity and 0.1°C for temperature. The sensor also has a temperature accuracy of +/- 0.5°C and a humidity accuracy of +/- 3%.

Credits This library was developed by Szymon Nyderek and Opend AI Assistant based on the [datasheet for the ATH10 sensor].

License This library is released under the MIT license. Feel free to use and modify the code as needed.

This library is work in progress and there can be some errors and warnings.
