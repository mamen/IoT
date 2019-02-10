#include <msp430.h> 

volatile int addrRead = 0b10000000;
volatile int addrWrite = 0b10000001;


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    // I2C Sensor-Pins: P1.6 & P1.7
    P4SEL0 |= 0x01; // Configure GPIO 4.0 SDA 1.7 SCL to I2C pins
    P4SEL1 |= 0x00; // Configure GPIO 4.1 SDA 1.7 SCL to I2C pins


    // read from sensor
    while(1){
        accel_update(0,0);
    }

    return 0;
}

