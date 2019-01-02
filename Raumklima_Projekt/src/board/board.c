/*
 * board.c
 *
 *  Created on: 2 Jan 2019
 *      Author: markus
 */

#include <msp430.h>

void board_init() {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1OUT = 0x06;

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    __enable_interrupt();

}
