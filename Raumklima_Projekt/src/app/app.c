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

    char buffer[7];

    floatToString(humidity, buffer, 1);

    buffer[4] = ' ';
    buffer[5] = 'H';
    buffer[6] = 'u';

    lcd_writeString(buffer);
}


void app_showAirQuality() {
//    int co2ppm = MQRead();

    char buffer[6];

    if(airQualityStatus == 0) {
        buffer[0] = 'A';
        buffer[1] = 'L';
        buffer[2] = 'L';
        buffer[3] = ' ';
        buffer[4] = 'O';
        buffer[5] = 'K';
    } else {
        buffer[0] = 'N';
        buffer[1] = 'O';
        buffer[2] = 'T';
        buffer[3] = ' ';
        buffer[4] = 'O';
        buffer[5] = 'K';
    }

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
    SHT21_init();
    adc_init();

    uart_init(UART1);
    led_init();

    mq135_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    app_updateDisplay();

    while(1) {

        while(!buttons_isButtonPressed(BUTTON_1) && !buttons_isButtonPressed(BUTTON_2)) {

            airQualityStatus = P8IN & 0x10;

            if(airQualityStatus == 0) {
                led_setMode(LED_RED, LED_MODE_ON);
            } else {
                led_setMode(LED_RED, LED_MODE_OFF);
            }

            system_sleep(500);
            app_updateDisplay();
        }

        if(buttons_isButtonPressed(BUTTON_1)) {

            app_switchState(DOWN);

            app_updateDisplay();
            system_sleep(200);

        }

        if(buttons_isButtonPressed(BUTTON_2)) {

            app_switchState(UP);

            app_updateDisplay();
            system_sleep(200);
        }

    }
}
