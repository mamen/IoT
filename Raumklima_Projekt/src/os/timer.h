/*
 * timer.h
 *
 *  Created on: 3 Feb 2019
 *      Author: markus
 */

#ifndef SRC_OS_TIMER_H_
#define SRC_OS_TIMER_H_

#include "../board/board.h"

typedef enum {
    Timer_A0,
    Timer_B0
} TIMER_t;

void timer_init(TIMER_t timer, int milliseconds);

#endif /* SRC_OS_TIMER_H_ */
