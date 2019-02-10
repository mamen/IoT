/*
 * adc.h
 *
 *  Created on: 9 Feb 2019
 *      Author: markus
 */

#ifndef SRC_HAL_ADC_H_
#define SRC_HAL_ADC_H_

#include <msp430.h>

#define ADC12_SHT_16 0x0200 // 16 clock cycles for sample and hold
#define ADC12_ON 0x0010 // Used to turn ADC12 peripheral on
#define ADC12_SHT_SRC_SEL 0x0200 // Selects source for sample & hold
#define ADC12_12BIT 0x0020 // Selects 12-bits of resolution
#define ADC12_P92 0x000A // Use input P9.2 for analog input

void adc_init();

#endif /* SRC_HAL_ADC_H_ */
