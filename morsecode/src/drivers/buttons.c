#include <msp430.h>
#include "buttons.h"

int buttons_isButtonPressed(int button) {

    int result = 0;

    switch(button) {
        case 1:
            if((P1IN & (1<<1)) == 0) {
                result = 1;
            }
            break;
        case 2:
            if((P1IN & (1<<2)) == 0) {
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
            P1REN |= BUTTON_S1_PIN;
            break;

        case 2:
            P1REN |= BUTTON_S2_PIN;
            break;
    }
}
