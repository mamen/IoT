#include "../gpio.h"

void gpio_multiplex(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_FUNC_t func) {

    switch(port) {
        case PORT1:

            switch(func) {
                case F1:
                    P1SEL0 &= ~(1 << func);
                    P1SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P1SEL0 &= ~(1 << func);
                    P1SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P1SEL0 |= ~(1 << func);
                    P1SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P1SEL0 |= ~(1 << func);
                    P1SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT2:

            switch(func) {
                case F1:
                    P2SEL0 &= ~(1 << func);
                    P2SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P2SEL0 &= ~(1 << func);
                    P2SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P2SEL0 |= ~(1 << func);
                    P2SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P2SEL0 |= ~(1 << func);
                    P2SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT3:

            switch(func) {
                case F1:
                    P3SEL0 &= ~(1 << func);
                    P3SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P3SEL0 &= ~(1 << func);
                    P3SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P3SEL0 |= ~(1 << func);
                    P3SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P3SEL0 |= ~(1 << func);
                    P3SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT4:

            switch(func) {
                case F1:
                    P4SEL0 &= ~(1 << func);
                    P4SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P4SEL0 &= ~(1 << func);
                    P4SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P4SEL0 |= ~(1 << func);
                    P4SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P4SEL0 |= ~(1 << func);
                    P4SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT5:

            switch(func) {
                case F1:
                    P5SEL0 &= ~(1 << func);
                    P5SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P5SEL0 &= ~(1 << func);
                    P5SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P5SEL0 |= ~(1 << func);
                    P5SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P5SEL0 |= ~(1 << func);
                    P5SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT6:

            switch(func) {
                case F1:
                    P6SEL0 &= ~(1 << func);
                    P6SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P6SEL0 &= ~(1 << func);
                    P6SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P6SEL0 |= ~(1 << func);
                    P6SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P6SEL0 |= ~(1 << func);
                    P6SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT7:

            switch(func) {
                case F1:
                    P7SEL0 &= ~(1 << func);
                    P7SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P7SEL0 &= ~(1 << func);
                    P7SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P7SEL0 |= ~(1 << func);
                    P7SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P7SEL0 |= ~(1 << func);
                    P7SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT8:

            switch(func) {
                case F1:
                    P8SEL0 &= ~(1 << func);
                    P8SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P8SEL0 &= ~(1 << func);
                    P8SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P8SEL0 |= ~(1 << func);
                    P8SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P8SEL0 |= ~(1 << func);
                    P8SEL1 |= ~(1 << func);
                    break;
            }

            break;

        case PORT9:

            switch(func) {
                case F1:
                    P9SEL0 &= ~(1 << func);
                    P9SEL1 &= ~(1 << func);
                    break;
                case F2:
                    P9SEL0 &= ~(1 << func);
                    P9SEL1 |= ~(1 << func);
                    break;
                case F3:
                    P9SEL0 |= ~(1 << func);
                    P9SEL1 &= ~(1 << func);
                    break;
                case F4:
                    P9SEL0 |= ~(1 << func);
                    P9SEL1 |= ~(1 << func);
                    break;
            }

            break;
    }


}

void gpio_toggle(GPIO_PORT_t port, GPIO_PIN_t pin) {
    switch(port) {

            case PORT1:
                P1OUT ^= (1 << pin);
                break;

            case PORT2:
                P2OUT ^= (1 << pin);
                break;

            case PORT3:
                P3OUT ^= (1 << pin);
                break;

            case PORT4:
                P4OUT ^= (1 << pin);
                break;

            case PORT5:
                P5OUT ^= (1 << pin);
                break;

            case PORT6:
                P6OUT ^= (1 << pin);
                break;

            case PORT7:
                P7OUT ^= (1 << pin);
                break;

            case PORT8:
                P8OUT ^= (1 << pin);
                break;

            case PORT9:
                P9OUT ^= (1 << pin);
                break;

        }
}

void gpio_setDirection(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_DIRECTION_t dir) {
    switch(port) {

        case PORT1:
            if(dir == OUTPUT) {
                P1DIR |= (1 << pin);
            } else {
                P1DIR &= ~(1 << pin);
            }
            break;

        case PORT2:
            if(dir == OUTPUT) {
                P2DIR |= (1 << pin);
            } else {
                P2DIR &= ~(1 << pin);
            }
            break;

        case PORT3:
            if(dir == OUTPUT) {
                P3DIR |= (1 << pin);
            } else {
                P3DIR &= ~(1 << pin);
            }
            break;

        case PORT4:
            if(dir == OUTPUT) {
                P4DIR |= (1 << pin);
            } else {
                P4DIR &= ~(1 << pin);
            }
            break;

        case PORT5:
            if(dir == OUTPUT) {
                P5DIR |= (1 << pin);
            } else {
                P5DIR &= ~(1 << pin);
            }
            break;

        case PORT6:
            if(dir == OUTPUT) {
                P6DIR |= (1 << pin);
            } else {
                P6DIR &= ~(1 << pin);
            }
            break;

        case PORT7:
            if(dir == OUTPUT) {
                P7DIR |= (1 << pin);
            } else {
                P7DIR &= ~(1 << pin);
            }
            break;

        case PORT8:
            if(dir == OUTPUT) {
                P8DIR |= (1 << pin);
            } else {
                P8DIR &= ~(1 << pin);
            }
            break;

        case PORT9:
            if(dir == OUTPUT) {
                P9DIR |= (1 << pin);
            } else {
                P9DIR &= ~(1 << pin);
            }
            break;

    }
}

void gpio_init() {
    // ULP Advisor > Rule 4.1 Terminate unused GPIOs
    // http://processors.wiki.ti.com/index.php/Compiler/diagnostic_messages/MSP430/10372
    PADIR |= (BIT_16_MASK);
    PBDIR |= (BIT_16_MASK);
    PCDIR |= (BIT_16_MASK);
    PDDIR |= (BIT_16_MASK);
    PEDIR |= (BIT_16_MASK);
    P1DIR |= (BIT_16_MASK);
    P2DIR |= (BIT_16_MASK);
    P3DIR |= (BIT_16_MASK);
    P4DIR |= (BIT_16_MASK);
    P5DIR |= (BIT_16_MASK);
    P6DIR |= (BIT_16_MASK);
    P7DIR |= (BIT_16_MASK);
    P8DIR |= (BIT_16_MASK);
    P9DIR |= (BIT_16_MASK);

    PAOUT &= ~(BIT_16_MASK);
    PBOUT &= ~(BIT_16_MASK);
    PCOUT &= ~(BIT_16_MASK);
    PDOUT &= ~(BIT_16_MASK);
    PEOUT &= ~(BIT_16_MASK);
    P1OUT &= ~(BIT_16_MASK);
    P2OUT &= ~(BIT_16_MASK);
    P3OUT &= ~(BIT_16_MASK);
    P4OUT &= ~(BIT_16_MASK);
    P5OUT &= ~(BIT_16_MASK);
    P6OUT &= ~(BIT_16_MASK);
    P7OUT &= ~(BIT_16_MASK);
    P8OUT &= ~(BIT_16_MASK);
    P9OUT &= ~(BIT_16_MASK);

    // i2c
    UCB0IFG = 0;
    UCB0CTLW0 = 0;
    UCB0CTL0 = 0;
    UCB0CTL1 = 0;

    // Primary module function is selected
    P1SEL0 |= (1 << 0x6) | (1 << 0x7);
    P1SEL0 |= BIT6 | BIT7;

    UCB0CTLW0 |= UCSWRST; // Software reset enabled
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSYNC | UCTR | UCSSEL__SMCLK; // I2C master mode, sync
    UCB0CTLW0 &= ~UCSWRST; // clear reset register
    UCB0BRW = 0x0008; // baud rate = SMCLK / 8
    UCB0CTLW1 = UCASTP_2; // Automatic stop generated after UCB0TBCNT is reached
    UCB0TBCNT = 0x02; // number of bytes to be sent/received

}
