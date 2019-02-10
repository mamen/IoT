/*
 * app.c
 *
 *  Created on: 7 Feb 2019
 *      Author: markus
 */
#include "app.h"

void app_showTemperature() {
    volatile float temperature = 0.0f;

    temperature = SHT21_readTemperature();

    char buffer[7];

    floatToString(temperature, buffer, 2);

    buffer[5] = '*';
    buffer[6] = 'C';

    lcd_writeString(buffer);
}

void app_showHumidity() {
    float humidity = SHT21_readHumidity();

    char buffer[5];

    floatToString(humidity, buffer, 2);

    lcd_writeString(buffer);
}


unsigned int ADC_value=0, ADC_value2=0;

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void) {

    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG)){
        case ADC12IV_ADC12IFG1:
            // ADC12MEM1 Interrupt
            ADC_value = ADC12MEM0;// Save MEM0
            ADC_value2 = ADC12MEM1;// Save MEM1

            char buff[128];

//            intToString(ADC_value, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");
//
//            intToString(ADC_value2, buff);
//            uart_writeString(UART1, buff);
//            uart_writeString(UART1, "\r\n");

            float Ro = 9.83;
//
            float resistance = ((1023.0/ADC_value2) * 5. - 1.)*RLOAD;

            float ppm = PARA * pow((resistance/ (resistance * pow((ATMOCO2/PARA), (1.0/PARB)))), -PARB);

            // source: https://angeloloza.blogspot.com/2016/06/android-arduino-air-quality-monitor.html
//            float realVal = 114.3544 * pow((ADC_value2 / Ro), -2.93599);

            floatToString(ppm, buff, 0);
            lcd_writeString(buff);


            uart_writeString(UART1, buff);
            uart_writeString(UART1, "\r\n");


//            __bic_SR_register_on_exit(LPM0_bits|GIE); // Exit CPU, clearinterrupts
        break;
        default:
            break;
    }
}


void app_showAirQuality() {

    ADC12CTL0 |= ADC12ENC | ADC12SC;
//    __bis_SR_register(LPM0_bits + GIE);
}

void app_updateDisplay() {

    switch(currentState) {
        case TEMPERATURE:
            app_showTemperature();
            break;
        case HUMIDITY:
            app_showHumidity();
         break;
        case AIRQUALITY:
            app_showAirQuality();
         break;
    }
}

void app_switchState(SwitchDirection_t dir) {

    if(dir == UP) {
        switch(currentState) {
            case TEMPERATURE:
                currentState = AIRQUALITY;
                break;
            case HUMIDITY:
                currentState = TEMPERATURE;
             break;
            case AIRQUALITY:
                currentState = HUMIDITY;
             break;
        }
    } else {
        switch(currentState) {
            case TEMPERATURE:
                currentState = HUMIDITY;
                break;
            case HUMIDITY:
                currentState = AIRQUALITY;
             break;
            case AIRQUALITY:
                currentState = TEMPERATURE;
             break;
        }
    }
}

void app_run() {

    board_init();
    gpio_init();


    system_systickInit();
    buttons_init();


    lcd_init();
    uart_init(UART1);

    SHT21_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    adc_init();

    app_updateDisplay();

    while(1) {

        while(!buttons_isButtonPressed(BUTTON_1) && !buttons_isButtonPressed(BUTTON_2)) {
            system_sleep(500);
            app_updateDisplay();
        }

        if(buttons_isButtonPressed(BUTTON_1)) {
            system_sleep(200);

            app_switchState(DOWN);

            app_updateDisplay();

        }

        if(buttons_isButtonPressed(BUTTON_2)) {
            system_sleep(200);

            app_switchState(UP);

            app_updateDisplay();
        }

    }
}
