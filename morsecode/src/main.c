#include <stdio.h>
#include <msp430.h>
#include "drivers/led.h"
#include "drivers/buttons.h"
#include "main.h"


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
        // no button is pressed

        // if the counter is > 0 and no button is pressed:
        // ==> button got released
        if(pressCounter > 0) {
            // . = dit = 60ms
            // - = dah = 180ms

            float minValue = (float)(ditDuration * (1 - (percentageOff/100)));
            float maxValue = (float)(ditDuration * (1 + (percentageOff/100)));

            // check if dit or dah?
            if((float)pressCounter >= minValue &&
               (float)pressCounter <= maxValue) {
                    // dit

                    sequence[signCount] = '.';
                    signCount++;
                    led_glowForMs(LED_GREEN, 500);

                    led_toggleLED(LED_RED, LED_MODE_OFF);

                    if(firstChar == 1)
                        firstChar = 0;

            } else if((float)pressCounter >= minValue &&
                      (float)pressCounter <= maxValue) {
                    // dah

                    sequence[signCount] = '-';
                    signCount++;
                    led_glowForMs(LED_GREEN, 500);

                    led_toggleLED(LED_RED, LED_MODE_OFF);

                    if(firstChar == 1)
                        firstChar = 0;
            } else {

                // error
                currentState = FAILURE;

            }

            pressCounter = 0;

        } else {
            // no button was pressed -> pause
            pauseCounter++;
        }
    }

    // break between words
    if(pauseCounter % 180 == 0 && firstChar == 0) {
        sequence[signCount] = '_';
        signCount++;
    }

    // if 10 seconds have passed => check the input
    if(currentState == INPUT && pauseCounter > 10000) {
        currentState = CHECK_INPUT;
        pauseCounter = 0;
    }

}

void checkInput() {

    volatile int success = 1;
    volatile int i = 0;

    for(i = 0; i < sizeof(wordToMorse); i++) {
        if(sequence[i] != wordToMorse[i]) {
            success = 0;
        }
    }

    for(i = sizeof(wordToMorse); i < sizeof(sequence); i++) {
       if(sequence[i] != '_' && sequence[i] != '\x00') {
           success = 0;
       }
   }

    // light up green LED for 10s
    if(success == 1) {
        led_glowForMs(LED_GREEN, 10000);
        currentState = WAITING_FOR_RESTART;
    } else {
        led_glowForMs(LED_RED, 10000);
        currentState = WAITING_FOR_RESTART;
    }


}

void waitForRestart() {

    if(led_getCurrentMode(LED_RED) == LED_MODE_OFF &&
            led_getCurrentMode(LED_GREEN) == LED_MODE_OFF) {

        currentState = INPUT;
    }
}

void checkFailure() {
    // delete sequence
    volatile unsigned int i = 0;

    for(i = 0; i < sizeof(sequence); i++)
    {
        sequence[i] = '\x00';
    }


    // glow red led for 10 seconds
    led_glowForMs(LED_RED, 10000);

    currentState = WAITING_FOR_RESTART;
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

        case WAITING_FOR_RESTART:
            waitForRestart();
            break;

        case FAILURE:
            checkFailure();
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







