#include <msp430.h>
#include <stdio.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings --> Pins aktivieren

    // set Input/Output pins

    // P1
    // 0 .. OUT -> 1 | LED 1
    // 1 .. IN  -> 0 | S1
    // 2 .. IN  -> 0 | S2
    // P1DIR = 0000 0001 => 0x01

    // P9
    // 7 .. OUT -> 1 | LED 2
    // P9DIR = 0100 0000 => 0x07

    P1DIR = (1<<0);
    P9DIR = (1<<7);

    P1OUT = 0x06;
    P9OUT = 0x06;

    // pull-up resistor fuer S1 und S2
    P1REN |= (1<<1);
    P1REN |= (1<<2);


    for(;;) {
        // S1 gedrueckt
        if((P1IN & (1<<1)) == 0) {
            // toggle LED
            P1OUT ^= 0x01;
        }

        //S1 gedrueckt
        if((P1IN & (1<<2)) == 0) {
            // toggle LED
            P9OUT ^= (1<<7);
        }
    }




    return 0;
}
