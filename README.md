# DS3231_for_STM32_HAL
An STM32 HAL library written for the DS3231 real-time clock IC.
### STM32CubeMX setup
* In STM32CubeMX, set I2C1 to "I2C" and USART1 to "asynchronous"
* Set up an external interrupt pin (say PB0) in GPIO settings, use "external interrupt mode with falling edge trigger detection" and "pull-up" settings.
* Activate the external interrupt in NVIC settings by checking the corresponding box.
* Connect pin 3 (INT#/SQW) of the DS3231 to this external interrupt pin.
* Save and generate code.

### IDE setup
* In your IDE, include [`ds3231_for_stm32_hal.h`](./ds3231_for_stm32_hal.h) and [`ds3231_for_stm32_hal.c`](./ds3231_for_stm32_hal.c).
* Complie and flash program to microcontroller.
* Read the results from a UART monitor/plotter.
* Refer to [./examples](./examples) ([`main.c`](./examples/main.c), [`stm32f4xx_it.c`](./examples/stm32f4xx_it.c)) and [datasheets](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf) for further information.
