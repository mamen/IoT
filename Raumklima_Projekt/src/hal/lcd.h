#ifndef LCD_H_
#define LCD_H_

#include <msp430.h>
#include <inttypes.h>
#include <string.h>

#define LCD_NUM_SEGMENTS 6

void lcd_init();
void lcd_clear();
void lcd_setDigit(int digit, uint8_t pos);
void lcd_setSymbol(int symbolIdx);
void lcd_writeString(char* string);

#endif /* LCD_H_ */
