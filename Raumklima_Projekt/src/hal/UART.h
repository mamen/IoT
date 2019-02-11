#ifndef SRC_HAL_UART_H_
#define SRC_HAL_UART_H_

//#include "hal.h"
#include <inttypes.h>
#include <stdbool.h>

#define UARTSYSCLK      (1000000)
#define UART1_CLKDIV_0     (0x68)
#define UART1_CLKDIV_1     (0x00)
#define UART0_CLKDIV_0     (0x68)
#define UART0_CLKDIV_1     (0x00)

typedef enum{
    UART0,
    UART1
} UART_t;

void uart_init();
void uart_writeByte(UART_t uart, const uint8_t byte);
void uart_writeString(UART_t uart, const uint8_t str[]);
void uart_readByte(UART_t uart, uint8_t *outValue);
void uart_readString(UART_t uart, uint8_t *outValue);
void uart_writeWord(UART_t uart, const uint16_t word);
bool uart_txBufIsEmpty(UART_t uart);
bool uart_rxHasByte(UART_t uart);


#endif /* SRC_HAL_UART_H_ */
