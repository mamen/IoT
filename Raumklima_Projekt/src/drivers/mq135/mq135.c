#include "mq135.h"

volatile static uint8_t readingComplete = 0;
volatile static float curVal = 0.0;

void mq135_init() {
    // 8.4 input from MQ135 DigitalOut
    gpio_setDirection(PORT8, PIN4, INPUT);
}

double mq135_getPercentage(double val, float pcurve[]) {
    return (pow(10, (((log(val)-pcurve[1])/ pcurve[2]) + pcurve[0])));
}

float mq135_read() {

    ADC12CTL0 |= ADC12ENC | ADC12SC;                        // start ADC readings

//    float COCurve[3] = {2.3, 0.72, -0.34};

//    double result = mq135_getPercentage(curVal, COCurve);

    float result = 662.9382 * pow(curVal, -4.0241);

    return result;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void) {

    if(ADC12MEM0 < 0x7FFF && ADC12MEM0 != 0) {
        curVal = (ADC12MEM0 & 0x0FFF) * (3.3/4096);
    }
}
