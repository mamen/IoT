#include "app.h"

void app_showTemperature() {
    volatile float temperature = 0.0f;

    temperature = SHT21_readTemperature();

    // +1 for period
    char buffer[LCD_NUM_SEGMENTS+1];

    floatToString(temperature, buffer, 2);

    removeNullCharacter(buffer, LCD_NUM_SEGMENTS+1);

    buffer[5] = '*';
    buffer[6] = 'C';

    lcd_writeString(buffer);
}

void app_showHumidity() {
    float humidity = SHT21_readHumidity();

    // +1 for period
    char buffer[LCD_NUM_SEGMENTS+1];

    floatToString(humidity, buffer, 1);

    removeNullCharacter(buffer, LCD_NUM_SEGMENTS+1);

    buffer[4] = ' ';
    buffer[5] = 'H';
    buffer[6] = 'u';

    lcd_writeString(buffer);
}


void app_showAirQuality() {
    float co2ppm = mq135_read();

    char buffer[LCD_NUM_SEGMENTS];

    intToString((int)co2ppm, buffer);

    removeNullCharacter(buffer, LCD_NUM_SEGMENTS);

    buffer[3] = 'C';
    buffer[4] = 'O';
    buffer[5] = '2';

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

    led_init();
    adc_init();
    mq135_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    app_updateDisplay();

    int airQualityStatus;

    while(1) {

        while(!buttons_isButtonPressed(BUTTON_1) && !buttons_isButtonPressed(BUTTON_2)) {

            // read digital-in on pin 8.4
            airQualityStatus = P8IN & 0x10;

            if(airQualityStatus == 0) {
                led_setMode(LED_RED, LED_MODE_ON);
            } else {
                led_setMode(LED_RED, LED_MODE_OFF);
            }

            system_sleep(10);
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
