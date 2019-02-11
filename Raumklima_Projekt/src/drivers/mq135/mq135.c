#include "mq135.h"

void MQ135_init() {


}

#define NUM_SAMPLES 1
#define READ_SAMPLE_INTERVAL 10


volatile float COCurve[3] = {2.3, 0.72, -0.34};

volatile uint8_t readingComplete = 0;
volatile float data[NUM_SAMPLES];
volatile int ro = 10;


mq135_init() {
    // 8.4 input from MQ135 DigitalOut
    gpio_setDirection(PORT8, PIN4, INPUT);
}


// MQGetPercentage(ration, COCurve);

float MQGetPercentage(float rs_ro_ratio, float pcurve[]) {
    return (pow(10, (((log(rs_ro_ratio)-pcurve[1])/ pcurve[2]) + pcurve[0])));
}

float MQRead() {

    ADC12CTL0 |= ADC12ENC | ADC12SC;
//    __bis_SR_register(LPM0_bits + GIE);

    while(readingComplete == 0);

    readingComplete = 0;

    volatile int i;
    volatile float rs = 0.0;

    for(i = 0; i < NUM_SAMPLES; i++) {
        rs += data[i];
    }

    rs = rs/ NUM_SAMPLES;

    float result = MQGetPercentage((rs/ro), COCurve);


    return result;

}

float MQResistanceCalculation(float raw_adc) {
//        return (float)RL_VALUE*(1023.0-raw_adc)/(float)raw_adc);
    return 0.0;
}
















// ----------------------------

volatile float ppm = -1;

int MQ135_read() {

    float result = MQRead();


    return 0;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void) {

//    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG)){
//        case ADC12IV_ADC12IFG1:


    if(ADC12MEM0 < 0x7FFF) {


            // ADC12MEM1 Interrupt
//            ADC_value = ADC12MEM0;// Save MEM0
//            ADC_value2 = ADC12MEM1;// Save MEM1

            char buff[128];

            float factor =  (3.3/4096);

            float value = (ADC12MEM0 & 0x0FFF) * factor;


        floatToString(value, buff, 2);
        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM1 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM2 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM3 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM4 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM5 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM6 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM7 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM8 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM9 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM10 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM11 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM12 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM13 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM14 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM15 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM16 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM17 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM18 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM19 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM20 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM21 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM22 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM23 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM24 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM25 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM26 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM27 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM28 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM29 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM30 * factor, buff, 2);
//        uart_writeString(UART1, buff);
//        uart_writeString(UART1, ", ");
//        floatToString(ADC12MEM31 * factor, buff, 2);
//        uart_writeString(UART1, buff);
        uart_writeString(UART1, ";\r\n");
//
//            uart_writeString(UART1, "ADC1: ");
//            floatToString(ADC_value, buff,0);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");
//
//            uart_writeString(UART1, "ADC2: ");
//            intToString(ADC_value2, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");
//
//            // 397
//
//            float Ro = 9.83;
////
//            float resistance = ((1023.0/ADC_value2) * 5. - 1.)*RLOAD;
//
//            ppm = PARA * pow((resistance/ (resistance * pow((ATMOCO2/PARA), (1.0/PARB)))), -PARB);
//
//            uart_writeString(UART1, "ppm: ");
//            floatToString(ppm, buff,5);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");
//
//            // source: https://angeloloza.blogspot.com/2016/06/android-arduino-air-quality-monitor.html
//            float realVal = 114.3544 * pow((ADC_value2 / Ro), -2.93599);
//
//            uart_writeString(UART1, "realVal: ");
//            floatToString(realVal, buff,5);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");

//            unsigned int ADC_value0 = ADC12MEM0;
//            intToString(ADC_value0, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, ", ");
//
//            unsigned int ADC_value1 = ADC12MEM1;
//            intToString(ADC_value1, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, ", ");
//
//            unsigned int ADC_value2 = ADC12MEM2;
//            intToString(ADC_value2, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, " = ");
//
//
//            float value = ADC_value1 * 5.0/1023.0;
//
//            float Rs = ((5.0/value)-1) * 20;
//
//            floatToString(Rs, buff, 2);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");
//
//
//            ppm = 0;


//            __bic_SR_register_on_exit(LPM0_bits|GIE);
//        break;
//        default:
//            break;
    }

    readingComplete = 1;
}
