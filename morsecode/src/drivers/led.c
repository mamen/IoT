#include <msp430.h>
#include "led.h"

volatile int numSeconds = 0;

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA1_ISR (void) {
    numSeconds++;

//    if(numSeconds >= 10) {
//        led_toggleLED(LED_RED, LED_MODE_TOGGLE);
//
//        numSeconds = 0;
//    }
    TA1CCTL1 &= ~CCIFG;
}

void led_init() {

    // timer
//    TA1CCR0 = 1000; // 10 ms @ 1MHz
//
//    TA1CCTL1 |= CCIE;
//    TA1CTL = TASSEL_2 | MC_2 | ID_1;

//    P1SEL0 |= (1<<0);
//

    P1DIR |= 0x01;
    P9DIR |= LED_PIN_GREEN;

    led_toggleLED(LED_RED, LED_MODE_OFF);
    led_toggleLED(LED_GREEN, LED_MODE_OFF);

}


void led_toggleLED(int ledNum, int mode) {
    switch(mode) {
        // off
        case 0:
            if(ledNum == 1)
                P1OUT &= ~LED_PIN_RED;
            else
                P9OUT &= ~LED_PIN_GREEN;
            break;
        // on
        case 1:
            if(ledNum == 1)
                P1OUT |= LED_PIN_RED;
            else
                P9OUT |= LED_PIN_GREEN;
            break;
        // toggle
        case 2:
            if(ledNum == 1)
                P1OUT ^= LED_PIN_RED;
            else
                P9OUT ^= LED_PIN_GREEN;
            break;
        // blink
        case 3:
            if(ledNum == 1)
                P1OUT ^= LED_PIN_RED;
            else
                P9OUT ^= LED_PIN_GREEN;
            break;

    }
}

int led_getCurrentMode(int ledNum) {
    if(ledNum == LED_RED) {
        volatile int x = P1OUT & 0x01;
        return P1OUT & 0x01;
    }

    if(ledNum == LED_GREEN) {
        volatile int x = (P1OUT >> 7) & 0x01;
        return (P1OUT >> 7) & 0x01;
    }
}

