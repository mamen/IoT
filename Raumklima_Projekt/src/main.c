
#include "board/board.h"
#include "hal/hal.h"
#include "drivers/sht21/sht21.h"



/**
 * main.c
 */
int main(void)
{

    board_init();
	gpio_init();

//	SHT21_init();



    uart_init(UART1);

	while(1) {
	    SHT21_readTemperature();
	}

	return 0;
}
