#include <msp430.h>
#include "drivers/led.h"


/**
 * main.c
 */


static volatile int pressCounter = 0;
static volatile int ditDuration = 60;
static volatile int dahDuration = 180;
static volatile int percentageOff = 10;
static volatile char sequence[100];
static volatile int signCount = 0;


static volatile int test = 0;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR (void) {

    /*
    if(test < 10) {
        // off
        led_toggleLED(LED_RED, LED_MODE_OFF);
        led_toggleLED(LED_GREEN, LED_MODE_OFF);
        test++;
    } else {
        // on
        led_toggleLED(LED_RED, LED_MODE_ON);
        led_toggleLED(2, LED_MODE_ON);
        test = 0;
    }
    */

    // if any button is pressed
    if(
            (P1IN & (1<<1)) == 0 ||
            (P1IN & (1<<2)) == 0
    ) {
        // increment the counter
        pressCounter++;
    } else {

        // if the counter is > 0 and no button is pressed:
        // ==> button got released
        if(pressCounter > 0) {
            // . = dit = 60ms
            // - = dah = 180ms

            // dit
            if(
                    pressCounter >= (ditDuration * (1 - (percentageOff/100))) &&
                    pressCounter <= (ditDuration * (1 + (percentageOff/100)))
                ) {
                    sequence[signCount] = '.';
                    signCount++;
            }

            // dah
            if(
                    pressCounter >= (dahDuration * (1 - (percentageOff/100))) &&
                    pressCounter <= (dahDuration * (1 + (percentageOff/100)))
                ) {
                    sequence[signCount] = '-';
                    signCount++;
            }

            pressCounter = 0;

        }
    }


}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    // set Input/Output pins
    // P1
    // 0 .. OUT -> 1 | LED 1
    // 2 .. IN  -> 0 | S2
    // 1 .. IN  -> 0 | S1
    // P1DIR = 0000 0001 => 0x01
    // P9
    // 7 .. OUT -> 1 | LED 2
    // P9DIR = 0100 0000 => (1<<7)




    //pullup resistor for S1 & S2
    P1REN |= (1<<1);
    P1REN |= (1<<2);

    TA0CCR0 = 1000; // 1 ms @ 1MHz

    TA0CCTL1 |= CCIE;
    TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR;

    led_init();

    led_toggleLED(LED_RED, LED_MODE_ON);

    _enable_interrupt();


    while (1) {
    }

    return 0;
}







