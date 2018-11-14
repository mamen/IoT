#include <msp430.h>
#include "drivers/led.h"
#include "drivers/buttons.h"
#include "main.h"


static volatile State currentState;


void handleInput() {

    // if any button is pressed
    if(buttons_isButtonPressed(BUTTON_1) ||
       buttons_isButtonPressed(BUTTON_2)) {

        // light up red LED while button is pressed
        if(led_getCurrentMode(LED_RED) == LED_MODE_OFF) {
            led_toggleLED(LED_RED, LED_MODE_ON);
        }

        // increment the counter
        pressCounter++;
    } else {

        // switch off the LED
        led_toggleLED(LED_RED, LED_MODE_OFF);

        // if the counter is > 0 and no button is pressed:
        // ==> button got released
        if(pressCounter > 0) {
            // . = dit = 60ms
            // - = dah = 180ms

            float minValue = (float)(ditDuration * (1 - (percentageOff/100)));
            float maxValue = (float)(ditDuration * (1 + (percentageOff/100)));

            // dit or dah?
            if((float)pressCounter >= minValue &&
               (float)pressCounter <= maxValue) {
                    // dit

                    sequence[signCount] = '.';
                    signCount++;
                    led_glowForMs(LED_GREEN, 500);

            } else if((float)pressCounter >= minValue &&
                      (float)pressCounter <= maxValue) {
                    // dah

                    sequence[signCount] = '-';
                    signCount++;
                    led_glowForMs(LED_GREEN, 500);

            } else {

                // error
                currentState = FAILURE;

            }

            pressCounter = 0;

        }
    }


}

void checkInput() {

}

void checkSuccess() {

}

void checkFailure() {
    // delete sequence
    volatile int i;

    for(i = 0; i < sizeof(sequence); i++)
    {
        sequence[i] = '\x00';
    }


    // glow red led for 10 seconds
    led_glowForMs(LED_RED, 1000);

    currentState = IDLE;
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR (void) {

    switch(currentState) {
        case INPUT:
            handleInput();
            break;

        case CHECK_INPUT:
            checkInput();
            break;

        case SUCCESS:
            checkSuccess();
            break;

        case FAILURE:
            checkFailure();
            break;

        case IDLE:
            if(led_getCurrentMode(LED_RED) == LED_MODE_OFF &&
               led_getCurrentMode(LED_GREEN) == LED_MODE_OFF) {
               currentState = INPUT;
            }
            break;
    }


    TA0CCTL0 &= ~CCIFG;

}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1OUT = 0x06;

    led_init();

    buttons_enableButton(BUTTON_1);
    buttons_enableButton(BUTTON_2);

    currentState = INPUT;

    // Timer --------------------------
    TA0CCR0 = 10000; // 1 ms @ 1MHz

    TA0CCTL0 |= CCIE;
    TA0CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;
    // --------------------------------

    _enable_interrupt();

    while (1);

    return 0;
}







