#ifndef SRC_DRIVERS_MQ135_MQ135_H_
#define SRC_DRIVERS_MQ135_MQ135_H_


#include <msp430.h>
#include "../../utils/stringUtils.h"
#include "../../hal/adc.h"
#include "../../hal/uart.h"

// MQ 135 ---------------
// The load resistance on the board
#define RLOAD 10.0
// Calibration resistance at atmospheric CO2 level
#define RZERO 76.63
// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13
// ----------------------



float MQGetPercentage(float rs_ro_ratio, float pcurve[3]);
float MQRead();

void MQ135_init();
int MQ135_read();
__interrupt void ADC12_ISR(void);


#endif /* SRC_DRIVERS_MQ135_MQ135_H_ */
