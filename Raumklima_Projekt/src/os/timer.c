#include "timer.h"


void timer_init(TIMER_t timer, int milliseconds) {
    switch(timer) {
    case Timer_A0:
        // Timer --------------------------
        TA0CCR0 = milliseconds; // 1 ms @ 1MHz
        TA0CCTL0 |= CCIE;
        TA0CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;
        TA0CCTL0 &= ~CCIFG;
        // --------------------------------

//        _enable_interrupt();
        break;

    case Timer_B0:
        TA1CCR0 = milliseconds;
        TA1CCTL0 |= CCIE;
        TA1CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;
        TA1CCTL0 &= ~CCIFG;
        break;
    }
}
