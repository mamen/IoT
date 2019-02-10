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


// MQ 135 ---------------
/// The load resistance on the board
#define RLOAD 10.0
/// Calibration resistance at atmospheric CO2 level
#define RZERO 76.63
/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

/// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13
// ----------------------


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


void app_showTemperature();
void app_showHumidity();
void app_updateDisplay();
void app_showAirQuality();
void app_switchState(SwitchDirection_t dir);
void app_run();


#endif /* SRC_APP_APP_H_ */
