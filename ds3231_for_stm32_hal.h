
/* An STM32 HAL library written for the DS3231 real-time clock IC. */
/* Library by @eepj www.github.com/eepj */
#ifndef DS3231_FOR_STM32_HAL_H
#define DS3231_FOR_STM32_HAL_H
#include "main.h"
/*----------------------------------------------------------------------------*/
#define DS3231_I2C_ADDR 	0x68
#define DS3231_REG_SECOND 	0x00
#define DS3231_REG_MINUTE 	0x01
#define DS3231_REG_HOUR  	0x02
#define DS3231_REG_DOW    	0x03
#define DS3231_REG_DATE   	0x04
#define DS3231_REG_MONTH  	0x05
#define DS3231_REG_YEAR   	0x06
#define DS3231_REG_CONTROL 	0x0e
#define DS3231_TIMEOUT		HAL_MAX_DELAY
/*----------------------------------------------------------------------------*/
extern I2C_HandleTypeDef *_ds3231_ui2c;

void DS3231_Init(I2C_HandleTypeDef *hi2c);

void DS3231_SetClockHalt(uint8_t halt);
uint8_t DS3231_GetClockHalt(void);

void DS3231_SetRegByte(uint8_t regAddr, uint8_t val);
uint8_t DS3231_GetRegByte(uint8_t regAddr);

uint8_t DS3231_GetDayOfWeek(void);
uint8_t DS3231_GetDate(void);
uint8_t DS3231_GetMonth(void);
uint16_t DS3231_GetYear(void);

uint8_t DS3231_GetHour(void);
uint8_t DS3231_GetMinute(void);
uint8_t DS3231_GetSecond(void);
int8_t DS3231_GetTimeZoneHour(void);
uint8_t DS3231_GetTimeZoneMin(void);

void DS3231_SetDayOfWeek(uint8_t dow);
void DS3231_SetDate(uint8_t date);
void DS3231_SetMonth(uint8_t month);
void DS3231_SetYear(uint16_t year);

void DS3231_SetHour(uint8_t hour_24mode);
void DS3231_SetMinute(uint8_t minute);
void DS3231_SetSecond(uint8_t second);
void DS3231_SetTimeZone(int8_t hr, uint8_t min);

uint8_t DS3231_DecodeBCD(uint8_t bin);
uint8_t DS3231_EncodeBCD(uint8_t dec);

#endif
