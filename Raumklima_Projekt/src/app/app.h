#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include <stdlib.h>
#include "../board/board.h"
#include "../drivers/buttons.h"
#include "../drivers/led.h"
#include "../drivers/sht21/sht21.h"
#include "../drivers/mq135/mq135.h"
#include "../hal/hal.h"
#include "../os/timer.h"
#include "../os/system.h"
#include "../utils/stringUtils.h"

typedef enum {
    TEMPERATURE,
    HUMIDITY,
    AIRQUALITY
} State_t;

typedef enum {
    UP,
    DOWN
} SwitchDirection_t;

volatile static State_t currentState = AIRQUALITY;
volatile static int airQualityStatus;

void app_showTemperature();
void app_showHumidity();
void app_updateDisplay();
void app_showAirQuality();
void app_switchState(SwitchDirection_t dir);
void app_run();


#endif /* SRC_APP_APP_H_ */
