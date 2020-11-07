
/* An STM32 HAL library written for the DS3231 real-time clock IC. */
/* Library by @eepj www.github.com/eepj */
#include "ds3231_for_stm32_hal.h"
#include "main.h"
#ifdef __cplusplus
extern "C"{
#endif

I2C_HandleTypeDef *_ds3231_ui2c;

/**
 * @brief Initializes the DS3231 module. Sets clock halt bit to 0 to start timing.
 * @param hi2c User I2C handle pointer.
 */
void DS3231_Init(I2C_HandleTypeDef *hi2c) {
	_ds3231_ui2c = hi2c;
}

/**
 * @brief Gets clock halt bit.
 * @return Clock halt bit, 0 or 1.
 */
uint8_t DS3231_GetClockHalt(void) {
	return DS3231_GetRegByte(DS3231_REG_SECOND) & 0x40 >> 6;
}

/**
 * @brief Sets the byte in the designated DS3231 register to value.
 * @param regAddr Register address to write.
 * @param val Value to set, 0 to 255.
 */
void DS3231_SetRegByte(uint8_t regAddr, uint8_t val) {
	uint8_t bytes[2] = { regAddr, val };
	HAL_I2C_Master_Transmit(_ds3231_ui2c, DS3231_I2C_ADDR << 1, bytes, 2, DS3231_TIMEOUT);
}

/**
 * @brief Gets the byte in the designated DS3231 register.
 * @param regAddr Register address to read.
 * @return Value stored in the register, 0 to 255.
 */
uint8_t DS3231_GetRegByte(uint8_t regAddr) {
	uint8_t val;
	HAL_I2C_Master_Transmit(_ds3231_ui2c, DS3231_I2C_ADDR << 1, &regAddr, 1, DS3231_TIMEOUT);
	HAL_I2C_Master_Receive(_ds3231_ui2c, DS3231_I2C_ADDR << 1, &val, 1, DS3231_TIMEOUT);
	return val;
}

/**
 * @brief Gets the current day of week.
 * @return Days from last Sunday, 0 to 6.
 */
uint8_t DS3231_GetDayOfWeek(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_DOW));
}

/**
 * @brief Gets the current day of month.
 * @return Day of month, 1 to 31.
 */
uint8_t DS3231_GetDate(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_DATE));
}

/**
 * @brief Gets the current month.
 * @return Month, 1 to 12.
 */
uint8_t DS3231_GetMonth(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_MONTH));
}

/**
 * @brief Gets the current year.
 * @return Year, 2000 to 2099.
 */
uint16_t DS3231_GetYear(void) {
	uint16_t cen = DS3231_GetRegByte(DS3231_REG_CENT) * 100;
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_YEAR)) + cen;
}

/**
 * @brief Gets the current hour in 24h format.
 * @return Hour in 24h format, 0 to 23.
 */
uint8_t DS3231_GetHour(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_HOUR) & 0x3f);
}

/**
 * @brief Gets the current minute.
 * @return Minute, 0 to 59.
 */
uint8_t DS3231_GetMinute(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_MINUTE));
}

/**
 * @brief Gets the current second. Clock halt bit not included.
 * @return Second, 0 to 59.
 */
uint8_t DS3231_GetSecond(void) {
	return DS3231_DecodeBCD(DS3231_GetRegByte(DS3231_REG_SECOND) & 0x7f);
}

/**
 * @brief Sets the current day of week.
 * @param dayOfWeek Days since last Sunday, 0 to 6.
 */
void DS3231_SetDayOfWeek(uint8_t dayOfWeek) {
	DS3231_SetRegByte(DS3231_REG_DOW, DS3231_EncodeBCD(dayOfWeek));
}

/**
 * @brief Sets the current day of month.
 * @param date Day of month, 1 to 31.
 */
void DS3231_SetDate(uint8_t date) {
	DS3231_SetRegByte(DS3231_REG_DATE, DS3231_EncodeBCD(date));
}

/**
 * @brief Sets the current month.
 * @param month Month, 1 to 12.
 */
void DS3231_SetMonth(uint8_t month) {
	DS3231_SetRegByte(DS3231_REG_MONTH, DS3231_EncodeBCD(month));
}

/**
 * @brief Sets the current year.
 * @param year Year, 2000 to 2099.
 */
void DS3231_SetYear(uint16_t year) {
	DS3231_SetRegByte(DS3231_REG_CENT, year / 100);
	DS3231_SetRegByte(DS3231_REG_YEAR, DS3231_EncodeBCD(year % 100));
}

/**
 * @brief Sets the current hour, in 24h format.
 * @param hour_24mode Hour in 24h format, 0 to 23.
 */
void DS3231_SetHour(uint8_t hour_24mode) {
	DS3231_SetRegByte(DS3231_REG_HOUR, DS3231_EncodeBCD(hour_24mode & 0x3f));
}

/**
 * @brief Sets the current minute.
 * @param minute Minute, 0 to 59.
 */
void DS3231_SetMinute(uint8_t minute) {
	DS3231_SetRegByte(DS3231_REG_MINUTE, DS3231_EncodeBCD(minute));
}

/**
 * @brief Sets the current second.
 * @param second Second, 0 to 59.
 */
void DS3231_SetSecond(uint8_t second) {
	uint8_t ch = DS3231_GetClockHalt();
	DS3231_SetRegByte(DS3231_REG_SECOND, DS3231_EncodeBCD(second | ch));
}

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */
uint8_t DS3231_DecodeBCD(uint8_t bin) {
	return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

/**
 * @brief Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param dec Decimal number to encode.
 * @return Encoded binary-coded decimal value.
 */
uint8_t DS3231_EncodeBCD(uint8_t dec) {
	return (dec % 10 + ((dec / 10) << 4));
}

#ifdef __cplusplus
}
#endif
