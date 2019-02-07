/*
 * app.h
 *
 *  Created on: 7 Feb 2019
 *      Author: markus
 */

#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include <stdlib.h>
#include "../board/board.h"
#include "../hal/hal.h"
#include "../os/timer.h"
#include "../os/system.h"
#include "../drivers/buttons.h"
#include "../drivers/sht21/sht21.h"
#include "../utils/stringUtils.h"


typedef enum {
    TEMPERATURE,
    HUMIDITY,
    CO2
} State_t;

typedef enum {
    UP,
    DOWN
} SwitchDirection_t;

volatile static State_t currentState = TEMPERATURE;


void app_showTemperature();
void app_showHumidity();
void app_updateDisplay();
void app_switchState(SwitchDirection_t dir);
void app_run();


#endif /* SRC_APP_APP_H_ */
