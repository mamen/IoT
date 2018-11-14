/*
 * main.h
 *
 *  Created on: Nov 14, 2018
 *      Author: markus
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

static volatile int pressCounter = 0;
static volatile float ditDuration = 60.0;
static volatile float dahDuration = 180.0;
static volatile float percentageOff = 50.0;
static volatile char sequence[100];
static volatile int signCount = 0;

static volatile int idleCounter = 0;

typedef enum states {INPUT, CHECK_INPUT, SUCCESS, FAILURE, IDLE} State;


#endif /* SRC_MAIN_H_ */
