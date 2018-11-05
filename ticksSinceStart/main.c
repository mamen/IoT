#include <msp430.h>
#define TRUE 1
#define LEDS_OUT P1OUT
#define LEDS_DIR P1DIR
#define LEDS_SEL P1SEL
#define LED_GREEN (0x01 << 6)
#define BUTTON (0x200)

#pragma vector=PORT1_VECTOR
__interrupt void port1_isr(void) {
    // NOTE: normally, a button needs debouncing!
    // clear interrupt flag
    BUTTON_IFG &= ~BUTTON;
    // toggle LED
    LEDS_OUT ^= LED_RED;
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    LEDS_SEL |= LED_GREEN; // assign LED cotrol to timer
    LEDS_DIR |= LED_GREEN;

    TA0CCR0 = 1000; // 1 ms @ 1MHz
    TA0CCR1 = TACCR0 / 4; // 25% duty cycle

    // no capture (->ignore CCISx, SCS, SCCI), Compare mode, Reset/Set outmode, ignore "rest"
    TA0CCTL1 = CM_0 | OUTMOD_7;

    // SMCLK, Divider /1, Up mode, clear counter
    TA0CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;

    while (TRUE) {
        // could also sleep here
    }
}
