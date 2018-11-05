#include <msp430.h>
#include "drivers/led.h"
#include "drivers/buttons.h"


/**
 * main.c
 */


static volatile int pressCounter = 0;
static volatile int ditDuration = 60;
static volatile int dahDuration = 180;
static volatile int percentageOff = 50;
static volatile char sequence[100];
static volatile int signCount = 0;


static volatile int test = 0;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR (void) {

//    if(test < 10) {
//        // off
//        led_toggleLED(LED_RED, LED_MODE_OFF);
//        led_toggleLED(LED_GREEN, LED_MODE_OFF);
//        test++;
//    } else {
//        // on
//        led_toggleLED(LED_RED, LED_MODE_ON);
//        led_toggleLED(2, LED_MODE_ON);
//        test = 0;
//    }

    // if any button is pressed
    if(
            buttons_isButtonPressed(BUTTON_1) ||
            buttons_isButtonPressed(BUTTON_2)
    ) {
        // increment the counter
        pressCounter++;
    } else {

        // if the counter is > 0 and no button is pressed:
        // ==> button got released
        if(pressCounter > 0) {
            // . = dit = 60ms
            // - = dah = 180ms


            // dit or dah?
            if(
                    pressCounter >= (ditDuration * (1 - (percentageOff/100))) &&
                    pressCounter <= (ditDuration * (1 + (percentageOff/100)))
                ) {
                    // dit

                    sequence[signCount] = '.';
                    signCount++;
                    led_toggleLED(LED_GREEN, LED_MODE_ON);
            } else if(
                    pressCounter >= (dahDuration * (1 - (percentageOff/100))) &&
                    pressCounter <= (dahDuration * (1 + (percentageOff/100)))
                ) {
                    // dah

                    sequence[signCount] = '-';
                    signCount++;
                    led_toggleLED(LED_RED, LED_MODE_ON);
            } else {
                led_toggleLED(LED_GREEN, LED_MODE_OFF);
                led_toggleLED(LED_RED, LED_MODE_OFF);
            }

            pressCounter = 0;

        }
    }


}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    led_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    P1OUT = 0x06;

//    led_toggleLED(LED_RED, LED_MODE_ON);
//    led_toggleLED(LED_GREEN, LED_MODE_ON);



    // Timer --------------------------
    TA0CCR0 = 10000; // 1 ms @ 1MHz

    TA0CCTL0 |= CCIE;
    TA0CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;

    _enable_interrupt();
    // --------------------------------

    while (1) {
    }

    return 0;
}







