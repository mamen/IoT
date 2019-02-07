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

void app_updateDisplay() {

    switch(currentState) {
        case TEMPERATURE:
            app_showTemperature();
            break;
        case HUMIDITY:
            app_showHumidity();
         break;
        case CO2:
            app_showTemperature();
         break;
    }
}

void app_switchState(SwitchDirection_t dir) {

    if(dir == UP) {
        switch(currentState) {
            case TEMPERATURE:
                currentState = CO2;
                break;
            case HUMIDITY:
                currentState = TEMPERATURE;
             break;
            case CO2:
                currentState = HUMIDITY;
             break;
        }
    } else {
        switch(currentState) {
            case TEMPERATURE:
                currentState = HUMIDITY;
                break;
            case HUMIDITY:
                currentState = CO2;
             break;
            case CO2:
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
//    uart_init(UART1);

    SHT21_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    app_updateDisplay();


    while(1) {


        while(!buttons_isButtonPressed(BUTTON_1) && !buttons_isButtonPressed(BUTTON_2)) {
            system_sleep(500);
            app_updateDisplay();
        }

        if(buttons_isButtonPressed(BUTTON_1)) {
            system_sleep(90);

            app_switchState(DOWN);

            app_updateDisplay();

        }

        if(buttons_isButtonPressed(BUTTON_2)) {
            system_sleep(90);

            app_switchState(UP);

            app_updateDisplay();
        }

    }
}
