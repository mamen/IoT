#include <stdint.h>
#include <msp430.h>
#include <inttypes.h>
#include "sht21.h"
#include "../../hal/hal.h"


void SHT21_init() {
    UCB0IFG = 0;
    UCB0CTLW0 = 0;
    UCB0CTL0 = 0;
    UCB0CTL1 = 0;

    // P1.6     P1.6/UCB0SIMO/UCB0SDA/TA0.1/S1
    // P1.7     P1.7/UCB0SOMI/UCB0SCL/TA0.2/S0

    // Primary module function is selected
    P1SEL0 |= (1 << 0x6) | (1 << 0x7);
    P1SEL0 |= BIT6 | BIT7;


    UCB0CTLW0 |= UCSWRST; // Software reset enabled
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSYNC | UCTR | UCSSEL__SMCLK; // I2C master mode, sync
    UCB0CTLW0 &= ~UCSWRST; // clear reset register
    UCB0BRW = 0x0008; // baud rate = SMCLK / 8
    UCB0CTLW1 = UCASTP_2; // Automatic stop generated after UCB0TBCNT is reached
    UCB0TBCNT = 0x02; // number of bytes to be sent/received

    //UCB0CTLW1 = UCASTP_2; // automatic STOP assertion
    UCB0CTLW1 = UCASTP_0; // no automatic STOP assertion

    UCB0I2CSA = SHT21_I2C_ADDRESS; //0x0040; // address slave is 100 0000b
    UCB0CTL1 &= ~UCSWRST; // eUSCI_B in operational state CLear reset

    UCB0IE &= ~UCTXIE;
    UCB0IE &= ~UCRXIE;
}

void SHT21_readTemperature(){


    SHT21_init();

    g_temp = 0.0f;


    // Send temperature read command
    UCB0CTL1 |= UCTXSTT;                    // Send start
    while(!(UCB0IFG & UCTXIFG0));           // Wait for tx interrupt flag
    UCB0TXBUF = SHT21_TEMP_NOBLOCK;         // Send data byte
    while(!(UCB0IFG & UCTXIFG0));           // Wait for tx interrupt flag
    UCB0CTLW0 |= UCTXSTP;                   // Send stop
    UCB0CTLW0 &= ~UCTR;                     // Change to receive
    while (UCB0CTLW0 & UCTXSTP);            // Ensure stop condition got sent


    // Setup timer for 85ms measurement delay
    TB0CCTL0 = CCIE;                          // TBCCR0 interrupt enabled
    TB0CCR0 = 5000;                         // (2800 ticks) * (1 second / 32768 ticks) = 97.6 ms > 85 ms required
    TB0CTL = TBSSEL__ACLK | MC__UP;           // ACLK, up mode

    __bis_SR_register(LPM3_bits);       // Enter LPM3 w/ interrupt


    // Read the current temperature
    UCB0CTL1 |= UCTXSTT;
    while(UCB0CTLW0 & UCTXSTT);             // Wait for ready
    while(!(UCB0IFG & UCRXIFG));            // Wait for receive
    g_shtRxArr[0] = UCB0RXBUF;              // Read first byte
    while(!(UCB0IFG & UCRXIFG));            // Wait for second byte
    g_shtRxArr[1] = UCB0RXBUF;              // Read second byte
    while(UCB0CTLW0 & UCTXSTP);             // Wait for stop


    // convert it to a float-value
    uint16_t tempRaw = ((uint16_t)g_shtRxArr[0] << 8) | (uint16_t)(g_shtRxArr[1]);
    g_temp = (float)(tempRaw & 0xFFFC);
    g_temp = -46.85f + 175.72f * (g_temp/65536.0f);


    char str[80];
    sprintf(str, "The room currently has about %d degrees.\r\n", (int)g_temp);


    uart_writeString(UART1, str);

}



void SHT21_readHumidity(){


    SHT21_init();

    g_hum = 0.0f;


    // Send humidity read command
    UCB0CTL1 |= UCTXSTT;                    // Send start
    while(!(UCB0IFG & UCTXIFG0));           // Wait for tx interrupt flag
    UCB0TXBUF = SHT21_HUM_NOBLOCK;          // Send data byte
    while(!(UCB0IFG & UCTXIFG0));           // Wait for tx interrupt flag
    UCB0CTLW0 |= UCTXSTP;                   // Send stop
    UCB0CTLW0 &= ~UCTR;                     // Change to receive
    while (UCB0CTLW0 & UCTXSTP);            // Ensure stop condition got sent


    // Setup timer for 29ms
    TB0CCTL0 = CCIE;                          // TBCCR0 interrupt enabled
    TB0CCR0 = 1300;                         // (960 ticks) * (1 second / 32768 ticks) = 39.7 ms > 29 ms required
    TB0CTL = TBSSEL__ACLK | MC__UP;           // ACLK, up mode

    __bis_SR_register(LPM3_bits);       // Enter LPM3 w/ interrupt


    // Start transfer
    UCB0CTL1 |= UCTXSTT;
    while(UCB0CTLW0 & UCTXSTT);             // Wait for ready
    while(!(UCB0IFG & UCRXIFG));            // Wait for receive
    g_shtRxArr[0] = UCB0RXBUF;              // Read first byte
    while(!(UCB0IFG & UCRXIFG));            // Wait for second byte
    g_shtRxArr[1] = UCB0RXBUF;              // Read second byte
    while(UCB0CTLW0 & UCTXSTP);             // Wait for stop


    uint16_t humRaw = ((uint16_t)g_shtRxArr[0] << 8) | (uint16_t)(g_shtRxArr[1]);
    g_hum = (float)(humRaw & 0xFFFC);
    g_hum = -6.0f + 125.0f * (g_hum/65536.0f);


    char str[80];
    sprintf(str, "The room currently has a humidity of %d percent.\r\n", (int)g_hum);


    uart_writeString(UART1, str);

}

// Timer B1 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
    TB0CTL &= ~MC_3;
    __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}
