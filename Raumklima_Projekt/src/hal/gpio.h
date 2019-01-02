/*
 * gpio.h
 *
 *  Created on: 19 Dec 2018
 *      Author: markus
 */

#ifndef SRC_HAL_GPIO_H_
#define SRC_HAL_GPIO_H_

#include "../board/board.h"

typedef enum {
    PORT1,
    PORT2,
    PORT3,
    PORT4,
    PORT5,
    PORT6,
    PORT7,
    PORT8,
    PORT9
} GPIO_PORT_t;

typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9
} GPIO_PIN_t;

typedef enum {
    F1,
    F2,
    F3,
    F4
} GPIO_FUNC_t;

typedef enum {
    OUTPUT,
    INPUT
} GPIO_DIRECTION_t;


void gpio_setDirection(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_DIRECTION_t dir);
void gpio_init();


#endif /* SRC_HAL_GPIO_H_ */
