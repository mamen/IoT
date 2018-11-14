#include <msp430.h>
#include "led.h"

volatile int numSeconds = 0;
volatile int numBlinks = 0;
volatile int maxNumBlinks = 5;

volatile int msToGlowRed = 0;
volatile int msGlowedRed = 0;
volatile int msToGlowGreen = 0;
volatile int msGlowedGreen = 0;

volatile int ledToGlowRed = 0;
volatile int ledToGlowGreen = 0;

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TimerA1_ISR (void) {

    if(ledToGlowRed == 1) {
        msGlowedRed++;

        if(msGlowedRed == msToGlowRed) {
            led_toggleLED(LED_RED, LED_MODE_OFF);
            ledToGlowRed = 0;
            msGlowedRed = 0;
            msToGlowRed = 0;
        }
    }

    if(ledToGlowGreen == 1) {
        msGlowedGreen++;

        if(msGlowedGreen == msToGlowGreen) {
            led_toggleLED(LED_GREEN, LED_MODE_OFF);
            ledToGlowGreen = 0;
            msGlowedGreen = 0;
            msToGlowGreen = 0;
        }
    }

    TA1CCTL0 &= ~CCIFG;
}

void led_init() {

    // timer
//    TA1CCR0 = 1000; // 10 ms @ 1MHz
//
//    TA1CCTL1 |= CCIE;
//    TA1CTL = TASSEL_2 | MC_2 | ID_1;

//    P1SEL0 |= (1<<0);

    P1DIR |= LED_PIN_RED;
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
            // timer
            TA1CCR0 = 999; // 10 ms @ 1MHz

            TA1CCTL0 |= CCIE;
            TA1CTL = TASSEL_2 | ID_2 | MC_1;
            break;

    }
}

int led_getCurrentMode(int ledNum) {
    if(ledNum == LED_RED) {
        return P1OUT & LED_PIN_RED;
    }

    if(ledNum == LED_GREEN) {
        return (P9OUT >> 7) & 0x01;
    }
}



void led_glowForMs(int ledNum, int ms) {

    if(ledNum == LED_RED) {
        msToGlowRed = ms;
        ledToGlowRed = 1;
    }

    if(ledNum == LED_GREEN) {
        msToGlowGreen = ms;
        ledToGlowGreen = 1;
    }

    led_toggleLED(ledNum, LED_MODE_ON);

    // timer
    TA1CCR0 = 999; // 1 ms @ 1MHz

    TA1CCTL0 |= CCIE;
    TA1CTL = TASSEL_2 | ID_0 | MC_1;

}

