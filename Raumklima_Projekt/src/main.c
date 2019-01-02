
#include "board/board.h"
#include "hal/hal.h"
#include "drivers/sht21/sht21.h"



/**
 * TODO:
 *
 * Display values on LCD
 * Switch display modes on LCD with buttons
 * Read CO2 sensor
 * Code-Cleanup
 *
 */


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
        SHT21_readHumidity();
	}

	return 0;
}
