#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../gpio.h"
#include "../uart.h"

void uart_init(UART_t uart)
{
    switch (uart)
    {
    case UART0:
        // Configure GPIO
        gpio_multiplex(PORT4, PIN2, F3);
        gpio_multiplex(PORT4, PIN3, F3);
        // Configure UART
        UCA0CTLW0 |= UCSWRST;
        UCA0CTLW0 |= UCSSEL_2;       // set clock source SMCLK - SMCLK 1MHz
        UCA0BR0 = UART0_CLKDIV_0;   // Baudrate register
        UCA0BR1 = UART0_CLKDIV_1;   // Baudrate register
        UCA0MCTLW |= UCBRS0;
        UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine*
        break;

    case UART1:
        //Configure GPIO
        gpio_multiplex(PORT3, PIN4, F3);
        gpio_multiplex(PORT3, PIN5, F3);
        // Configure UART
        UCA1CTLW0 |= UCSWRST;
        UCA1CTLW0 |= UCSSEL_2;
        UCA1BR0 = UART1_CLKDIV_0;
        UCA1BR1 = UART1_CLKDIV_1;
        UCA0MCTLW |= UCBRS0;
        UCA1CTLW0 &= ~UCSWRST;
        break;
    default:
        break;
    }
}

void uart_writeByte(UART_t uart, const uint8_t byte)
{
    switch (uart)
    {
    case UART0:
        while(!uart_txBufIsEmpty(uart));
            UCA0TXBUF = byte;
        break;
    case UART1:
        while(!uart_txBufIsEmpty(uart));
            UCA1TXBUF = byte;
        break;
    default:
        break;
    }
}

void uart_writeWord(UART_t uart, const uint16_t word)
{
    switch (uart)
    {
    case UART0:
        while(!uart_txBufIsEmpty(uart));
        UCA0TXBUF = ((word & 0xFF00)>>8);
        while(!uart_txBufIsEmpty(uart));
        UCA0TXBUF = (word & 0xFF);
        break;
    case UART1:
        while(!uart_txBufIsEmpty(uart));
        UCA1TXBUF = ((word & 0xFF00)>>8);
        while(!uart_txBufIsEmpty(uart));
        UCA1TXBUF = (word & 0xFF);
        break;
    default:
        break;
    }
}

void uart_writeFloat(UART_t uart, const float value) {
    if (uart_txBufIsEmpty(uart)) {

    }
}

void uart_writeString(UART_t uart, const uint8_t str[])
{
    switch (uart)
    {
    case UART0:
        while (*str != '\0')
        {
            /* Wait for the transmit buffer to be ready */
            if (uart_txBufIsEmpty(uart))
            {
                /* Transmit data */
                UCA0TXBUF = *str;
            }
            /* If there is a line-feed, add a carriage return */
            if (*str == '\n')
            {
                /* Wait for the transmit buffer to be ready */
                if (uart_txBufIsEmpty(uart))
                {
                    UCA0TXBUF = '\r';
                }
            }
            str++;
        }

        break;

    case UART1:
        while (*str != '\0')
        {
            /* Wait for the transmit buffer to be ready */
            if (uart_txBufIsEmpty(uart))
            {
                /* Transmit data */
                UCA1TXBUF = *str;
                /* If there is a line-feed, add a carriage return */
                if (*str == '\n')
                {
                    /* Wait for the transmit buffer to be ready */
                    if (uart_txBufIsEmpty(uart))
                    {
                        UCA1TXBUF = '\r';
                    }
                }
                str++;
            }
        }
        break;
    default:
        break;
    }
}

// Todo check if readByte function works properly
void uart_readByte(UART_t uart, uint8_t *outValue)
{
//    switch (uart)
//    {
//    case UART0:
//        while(!uart_rxHasByte(uart));
//            *outValue = UCA0RXBUF;
//        break;
//    case UART1:
//        while(!uart_rxHasByte(uart));
//            *outValue = UCA1RXBUF;
//        break;
//    default:
//        break;
//    }
}

// Todo check if the read string function works properly
void uart_readString(UART_t uart, uint8_t *outValue)
{
//    switch (uart)
//    {
//    case UART0:
//        while (!uart_rxHasByte(uart))
//        {
//            if (UCA0RXBUF != '\0' && UCA0RXBUF != '\r' && UCA0RXBUF != '\n')
//            {
//                *outValue = UCA0RXBUF;
//            }
//        }
//        break;
//    case UART1:
//        while (uart_rxHasByte(uart))
//        {
//            if (UCA1RXBUF != '\0' && UCA1RXBUF != '\r' && UCA1RXBUF != '\n')
//            {
//                *outValue = UCA1RXBUF;
//            }
//        }
//        break;
//    default:
//        break;
//    }
}

bool uart_txBufIsEmpty(UART_t uart)
{
    bool value = false;
    switch (uart)
    {
    case UART0:
        value = (UCA0IFG & UCTXIFG);
        break;
    case UART1:
        value = (UCA1IFG & UCTXIFG);
        break;
    default:
        break;
    }
    return value;
}

bool uart_rxHasByte(UART_t uart)
{
//    bool value = false;
//    switch (uart)
//    {
//    case UART0:
//        value = (UCA0IFG & UCRXIFG);
//        break;
//    case UART1:
//        value = (UCA1IFG & UCRXIFG);
//        break;
//    default:
//        break;
//    }
//    return value;
}
