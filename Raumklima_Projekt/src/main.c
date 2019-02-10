#include "app/app.h"


/**
 * TODO:
 *
 * Read CO2 sensor
 * Second timer for automatic display-update every ~5 seconds
 * Code-Cleanup
 *
 */
/**
 * main.c
 */
int main(void)
{

	app_run();


	return 0;
}

///* ADC interrupt */
//interrupt(ADC10_VECTOR) ADC10_ISR(void)
//{
//    __bic_SR_register_on_exit(CPUOFF);                      // Clear CPUOFF bit - ADC processing in main
//}

