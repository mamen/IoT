#ifndef SRC_DRIVERS_SHT21_SHT21_H_
#define SRC_DRIVERS_SHT21_SHT21_H_

#include <stdint.h>
#include <msp430.h>
#include <inttypes.h>
#include "../../hal/hal.h"
#include "../../os/system.h"

#define SHT21_I2C_ADDRESS  0x40
#define SHT21_TEMPERATURE_HOLD_MASTER 0xE3
#define SHT21_TEMP_NOBLOCK 0xF3
#define SHT21_HUM_NOBLOCK  0xF5
#define SCODE_SHT21_VALS 0x01

void SHT21_init();
float SHT21_readTemperature();
float SHT21_readHumidity();


#endif /* SRC_DRIVERS_SHT21_SHT21_H_ */
