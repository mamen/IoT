#include <msp430.h>
#include "os.h"
#include "scheduler.h"

void ATOMIC_START(void) {
    // Disable Interrupts
    _disable_interrupts();
}

void ATOMIC_END(void) {
    // Enable Interrupts
    _enable_interrupts();
}

void blink_green() {
    while(1) {
        P1OUT |= 1 << 0;
        P1OUT &= ~1 << 0;
    }
}

void blink_red() {
    while(1) {
        P1OUT |= 1 << 6;
        P1OUT &= ~1 << 6;
    }
}


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	
	_enable_interrupts();


	os_createThread(blink_green);
	os_createThread(blink_red);

    os_start();

	return 0;
}
