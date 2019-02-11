/*
 * led.h
 *
 *  Created on: Oct 31, 2018
 *      Author: markus
 */

#ifndef DRIVERS_LED_H_
#define DRIVERS_LED_H_

#include <msp430.h>

#define LED_PIN_RED (1<<0)
#define LED_PIN_GREEN (1<<7)

typedef enum {
    LED_MODE_OFF,
    LED_MODE_ON,
    LED_MODE_TOGGLE
} LED_STATE_t;

typedef enum {
    LED_RED,
    LED_GREEN
} LED_TYPE_t;

void led_init();
void led_setMode(LED_TYPE_t ledNum, LED_STATE_t mode);

#endif /* DRIVERS_LED_H_ */
