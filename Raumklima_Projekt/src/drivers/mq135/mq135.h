#ifndef SRC_DRIVERS_MQ135_MQ135_H_
#define SRC_DRIVERS_MQ135_MQ135_H_


#include <msp430.h>
#include "../../utils/stringUtils.h"
#include "../../hal/adc.h"
#include "../../hal/uart.h"


double mq135_getPercentage(double rs_ro_ratio, float pcurve[3]);
void mq135_init();
float mq135_read();
__interrupt void ADC12_ISR(void);


#endif /* SRC_DRIVERS_MQ135_MQ135_H_ */
