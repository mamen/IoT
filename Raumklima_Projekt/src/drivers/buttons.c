#include <msp430.h>
#include "buttons.h"


void buttons_init() {
    P1OUT = 0x06;
}

int buttons_isButtonPressed(int button) {

    int result = 0;

    switch(button) {
        case 1:
            if((P1IN & BUTTON_S1_PIN) == 0) {
                result = 1;
            }
            break;
        case 2:
            if((P1IN & BUTTON_S2_PIN) == 0) {
                result = 1;
            }
            break;
    }

    return result;

}

void buttons_enableButton(int button) {

    // set pull-up resistors
    switch(button) {
        case 1:
            P1REN |= (1 << BUTTON_S1_PIN);
            P1OUT |= (1 << BUTTON_S1_PIN);
            break;

        case 2:

            P2REN |= (1 << BUTTON_S2_PIN);
            P2OUT |= (1 << BUTTON_S2_PIN);
            break;
    }
}
