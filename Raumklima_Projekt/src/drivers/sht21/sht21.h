/*
 * sht21.h
 *
 *  Created on: 2 Jan 2019
 *      Author: markus
 */

#ifndef SRC_DRIVERS_SHT21_SHT21_H_
#define SRC_DRIVERS_SHT21_SHT21_H_

#include <stdint.h>

#define SHT21_I2C_ADDRESS  0x40
#define SHT21_TEMPERATURE_HOLD_MASTER 0xE3
#define SHT21_TEMP_NOBLOCK 0xF3
#define SHT21_HUM_NOBLOCK  0xF5

#define SCODE_SHT21_VALS 0x01

volatile unsigned char g_shtRxArr[2];
volatile float g_temp;
volatile float g_hum;

void SHT21_init();
void SHT21_readTemperature();
void SHT21_readHumidity();


#endif /* SRC_DRIVERS_SHT21_SHT21_H_ */
