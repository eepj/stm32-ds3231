# DS3231_for_STM32_HAL
An STM32 HAL library written for the DS3231 real-time clock IC.

## Quick start
### Minimal setup
![Setup](./examples/images/minimal_connections.bmp)

### STM32CubeMX setup
* In STM32CubeMX, set I2C1 to "I2C" and USART1 to "asynchronous"
* Set up an external interrupt pin (say PB0) in GPIO settings, use "external interrupt mode with falling edge trigger detection" and "pull-up" settings.
* Activate the external interrupt in NVIC settings by checking the corresponding box.
* Connect pin 3 (INT#/SQW) of the DS3231 to this external interrupt pin.
* Save and generate code.

### IDE setup
* In your IDE, include [`ds3231_for_stm32_hal.h`](./ds3231_for_stm32_hal.h) and [`ds3231_for_stm32_hal.c`](./ds3231_for_stm32_hal.c).

### Main program
#### Includes
* In `main.c` (main program body file), include:
```ruby
#include "ds3231_for_stm32_hal.h"
```

#### Initialization
* In `main.c`, before the main loop and after the system inits, call the DS3231 init function:
 ```ruby
DS3231_Init(&hi2c1);
 ```
#### Date and time settings
* Date functions:
```ruby
void DS3231_SetDayOfWeek(uint8_t dow); // <-- Number of days since Sunday, 1 to 7.
void DS3231_SetDate(uint8_t date);
void DS3231_SetMonth(uint8_t month);
void DS3231_SetYear(uint16_t year);
void DS3231_SetFullDate(uint8_t date, uint8_t month, uint8_t dow, uint16_t year);
```
* Time functions:
```ruby
void DS3231_SetHour(uint8_t hour_24mode);
void DS3231_SetMinute(uint8_t minute);
void DS3231_SetSecond(uint8_t second);
void DS3231_SetFullTime(uint8_t hour_24mode, uint8_t minute, uint8_t second);
```

#### Interrupt modes
* Set interrupt mode with:
```ruby
void DS3231_SetInterruptMode(DS3231_InterruptMode mode);
```
* Possible modes: square wave interrupt and alarm interrupt.
```ruby
typedef enum DS3231_InterruptMode{
    DS3231_SQUARE_WAVE_INTERRUPT, DS3231_ALARM_INTERRUPT
}DS3231_InterruptMode;
```
#### Square wave output
* With square wave interrupt mode selected, select interrupting rate with:
```ruby
void DS3231_SetRateSelect(DS3231_Rate rate);
```
* Possible rates 1 Hz, 1.024 kHz, 4.096 kHz or 8.912 kHz.
```ruby
typedef enum DS3231_Rate{
	DS3231_1HZ, DS3231_1024HZ, DS3231_4096HZ, DS3231_8192HZ
}DS3231_Rate;
```

#### Alarms
* Enable/disable alarms with:
```ruby
void DS3231_EnableAlarm1(DS3231_State enable);
void DS3231_EnableAlarm2(DS3231_State enable);
```
* Possible modes: enabled or disabled.
```ruby
typedef enum DS3231_State{
	DS3231_DISABLED, DS3231_ENABLED
}DS3231_State;
```

* Set alarm mode with:
```ruby
void DS3231_SetAlarm1Mode(DS3231_Alarm1Mode alarmMode);
void DS3231_SetAlarm2Mode(DS3231_Alarm2Mode alarmMode);
```
* Possible alarm modes (refer to table 2 of datasheets):
```ruby
typedef enum D3231_Alarm1Mode{
    DS3231_A1_EVERY_S = 0x0f, DS3231_A1_MATCH_S = 0x0e, DS3231_A1_MATCH_S_M = 0x0c,
    DS3231_A1_MATCH_S_M_H = 0x08, DS3231_A1_MATCH_S_M_H_DATE = 0x00, DS3231_A1_MATCH_S_M_H_DAY = 0x80,
}DS3231_Alarm1Mode;

typedef enum D3231_Alarm2Mode{
    DS3231_A2_EVERY_M = 0x07, DS3231_A2_MATCH_M = 0x06, DS3231_A2_MATCH_M_H = 0x04,
    DS3231_A2_MATCH_M_H_DATE = 0x00, DS3231_A2_MATCH_M_H_DAY = 0x80,
}DS3231_Alarm2Mode;
```

 ### Interrupts
 * Check for an alarm flag with:
 ```ruby
uint8_t DS3231_IsAlarm1Triggered();
uint8_t DS3231_IsAlarm2Triggered();
 ```
 
 * Clear an alarm flag with:
 ```ruby
 void DS3231_ClearAlarm1Flag();
 void DS3231_ClearAlarm2Flag();
 ```
 
 ### Misc
 * The following are available:
 ```ruby
 void DS3231_Enable32kHzOutput(DS3231_State enable);

uint8_t DS3231_IsOscillatorStopped();
uint8_t DS3231_Is32kHzEnabled();

int8_t DS3231_GetTemperatureInteger();
uint8_t DS3231_GetTemperatureFraction();
 ```
* Refer to [./examples](./examples) ([`main.c`](./examples/main.c), [`stm32f4xx_it.c`](./examples/stm32f4xx_it.c)) and [datasheets](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf) for further information.
