#include "../adc.h"

void adc_init() {

    // set P9.2 as ADC input
    gpio_multiplex(PORT9, PIN2, F4);

    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
    ADC12CTL1 |= ADC12SHP | ADC12CONSEQ_1;
    ADC12CTL2 |= ADC12RES_0;
    ADC12IER0 |= ADC12IE0;
    ADC12MCTL0 |= ADC12INCH_10 | ADC12VRSEL_1 | ADC12EOS;

}
