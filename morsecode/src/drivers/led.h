/*
 * led.h
 *
 *  Created on: Oct 31, 2018
 *      Author: markus
 */

#ifndef DRIVERS_LED_H_
#define DRIVERS_LED_H_

#define LED_RED 1
#define LED_GREEN 2

#define LED_PIN_RED (1<<0)
#define LED_PIN_GREEN (1<<7)

#define LED_MODE_OFF 0
#define LED_MODE_ON 1
#define LED_MODE_TOGGLE 2
#define LED_MODE_BLINK 3

void led_init();
void led_toggleLED(int ledNum, int mode);

#endif /* DRIVERS_LED_H_ */
