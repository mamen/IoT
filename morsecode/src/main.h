/*
 * main.h
 *
 *  Created on: Nov 14, 2018
 *      Author: markus
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

typedef enum states {INPUT, CHECK_INPUT, WAITING_FOR_RESTART, FAILURE} State;

static volatile unsigned int pressCounter = 0;
static volatile float ditDuration = 60.0;
static volatile float dahDuration = 180.0;
static volatile float percentageOff = 50.0;
static volatile char sequence[100];
static volatile unsigned int signCount = 0;
static volatile unsigned int firstChar = 1;
static volatile unsigned int pauseCounter = 0;
static volatile State currentState;


// AFFE
static volatile char wordToMorse[14] = {'.', '-', '_', '.', '.', '-', '.', '_', '.', '.', '-', '.', '_', '.'};

static volatile unsigned int idleCounter = 0;



#endif /* SRC_MAIN_H_ */
