#include "../adc.h"

/*
 * adc.c
 *
 *  Created on: 9 Feb 2019
 *      Author: markus
 */


void adc_init() {

    P9SEL1 |= BIT2; // Configure P9.2 for ADC
    P9SEL0 |= BIT2;

    ADC12CTL0 = ADC12SHT0_2 | ADC12ON | ADC12MSC;
    ADC12CTL1 |= ADC12SHP | ADC12CONSEQ_1;
    ADC12CTL2 |= ADC12RES_2;
    ADC12IER0 |= ADC12IE1;
    ADC12MCTL0 |= ADC12INCH_3 | ADC12VRSEL_1;
    ADC12MCTL1 |= ADC12INCH_4 | ADC12VRSEL_1 | ADC12EOS;

}
