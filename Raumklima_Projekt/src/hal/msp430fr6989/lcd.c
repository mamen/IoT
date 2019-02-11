#include "../lcd.h"


void lcd_init(){

    /* set lcd pins and mux mode 4*/
    LCDCPCTL0 |= LCDS14 | LCDS15;           // pins for digit pos 0
    LCDCPCTL1 |= LCDS28 | LCDS29;           // pins for digit pos 1
    LCDCPCTL2 |= LCDS36 | LCDS37 | LCDS38;  // pins for digit pos 2 + .
    LCDCPCTL0 |= LCDS6 | LCDS7;             // pins for digit pos 3
    LCDCPCTL0 |= LCDS10 | LCDS11 | LCDS12;  // pins for digit pos 4 + :
    LCDCPCTL1 |= LCDS18 | LCDS19;           // pins for digit pos 5
    LCDCPCTL0 |= LCDS4;                     // pin for TMR

    LCDCCTL0 = LCD4MUX | LCDDIV4;  //    #define LCD4MUX (LCDMX1+LCDMX0+LCDSON)
    LCDCCTL0 |= LCDON;

    lcd_clear();
}

void lcd_clear(){
    LCDCMEMCTL = LCDCLRM;
}

void lcd_setPosition(int pos, uint8_t symbolCode) {
    switch (pos){
            case 0:
                LCDM8 = symbolCode;    // LCDM8 -> S15/S14
                break;
            case 1:
                LCDM15 = symbolCode;   // LCDM15 -> S29/S28
                break;
            case 2:
                LCDM19 = symbolCode;   // LCDM19 -> S37/S36
                break;
            case 3:
                LCDM4 = symbolCode;    // LCDM4 -> S7/S6
                break;
            case 4:
                LCDM6 = symbolCode;    // LCDM6 -> S11/S10
                break;
            case 5:
                LCDM10 = symbolCode;   // LCDM10 -> S19/S18
                break;
            default:
                break;
        }
}


void lcd_writeNumber(int pos, uint8_t digit) {

    uint8_t symbolCode;

    switch(digit){
        case 0:
            symbolCode = 0xFC;   // 0
            break;
        case 1:
            symbolCode = 0x60;   // 1
            break;
        case 2:
            symbolCode = 0xDB;   // 2
            break;
        case 3:
            symbolCode = 0xF3;   // 3
            break;
        case 4:
            symbolCode = 0x67;   // 4
            break;
        case 5:
            symbolCode = 0xB7;   // 5
            break;
        case 6:
            symbolCode = 0xBF;   // 6
            break;
        case 7:
            symbolCode = 0xE0;   // 7
            break;
        case 8:
            symbolCode = 0xFF;   // 8
            break;
        case 9:
            symbolCode = 0xF7;   // 9
            break;
        case 98:
            LCDM7 = 0x04;       // :
            return;
        case 99:
            LCDM20 = 0x01;      // .
            return;
        default:
            symbolCode = 0x00;
            break;
    }

    lcd_setPosition(pos, symbolCode);
}



void lcd_writeChar(int pos, char c){

    uint8_t symbolCode;

    switch(c){
        case ' ':
            symbolCode = 0x00;
            break;
        case '0':
            symbolCode = 0xFC;   // 0
            break;
        case '1':
            symbolCode = 0x60;   // 1
            break;
        case '2':
            symbolCode = 0xDB;   // 2
            break;
        case '3':
            symbolCode = 0xF3;   // 3
            break;
        case '4':
            symbolCode = 0x67;   // 4
            break;
        case '5':
            symbolCode = 0xB7;   // 5
            break;
        case '6':
            symbolCode = 0xBF;   // 6
            break;
        case '7':
            symbolCode = 0xE0;   // 7
            break;
        case '8':
            symbolCode = 0xFF;   // 8
            break;
        case '9':
            symbolCode = 0xF7;   // 9
            break;
        case '*':
            symbolCode = 0xC7;   // 0
            break;
        case 'A':
            symbolCode = 0xEF;   // 0
            break;
        case 'B':
            symbolCode = 0xFD;   // 1
            break;
        case 'C':
            symbolCode = 0x9C;   // 2
            break;
        case 'D':
            symbolCode = 0xF0;   // 3
            break;
        case 'E':
            symbolCode = 0x9F;   // 4
            break;
        case 'F':
            symbolCode = 0x8E;   // 5
            break;
        case 'G':
            symbolCode = 0xBD;   // 6
            break;
        case 'H':
            symbolCode = 0x6F;   // 7
            break;
        case 'I':
            symbolCode = 0xC;   // 8
            break;
        case 'J':
            symbolCode = 0x78;   // 9
            break;
        case 'K':
            symbolCode = 0x6D;   // 9
            break;
        case 'L':
            symbolCode = 0x1C;   // 9
            break;
        case 'M':
            symbolCode = 0x6C;   // 9
            break;
        case 'N':
            symbolCode = 0x6C;   // 9
            break;
        case 'o':
            symbolCode = 0x3B;   // 9
            break;
        case 'O':
            symbolCode = 0xFC;   // 9
            break;
        case 'P':
            symbolCode = 0xAF;   // 9
            break;
        case 'Q':
            symbolCode = 0xF7;   // 9
            break;
        case 'R':
            symbolCode = 0xF7;   // 9
            break;
        case 'S':
            symbolCode = 0xB7;   // 9
            break;
        case 'T':
            symbolCode = 0x8C;   // 9
            break;
        case 'u':
            symbolCode = 0x38;   // 9
            break;
        case 'U':
            symbolCode = 0x7C;   // 9
            break;
        case 'V':
            symbolCode = 0xF7;   // 9
            break;
        case 'W':
            symbolCode = 0xF7;   // 9
            break;
        case 'X':
            symbolCode = 0xF7;   // 9
            break;
        case 'Y':
            symbolCode = 0xF7;   // 9
            break;
        case 'Z':
            symbolCode = 0xF7;   // 9
            break;
        case '.':
            LCDM7 = 0x01;      // left .
//            LCDM20 = 0x01;      // right .
            return;
        case 98:
            LCDM7 = 0x04;       // :
            return;
        default:
            symbolCode = 0x00;
            break;
    }

    lcd_setPosition(pos, symbolCode);
}


void lcd_setSymbol(int symbolIdx) {

    switch(symbolIdx) {
        case 0:
            LCDM3 = 0x04;       // heart
            break;
        case 1:
            LCDM3 = 0x01;      // !
            break;
        case 2:
            LCDM3 = 0x08;       // clock symbol
            break;
        case 3:
            break;
    }
}

void lcd_writeString(char* string) {

    lcd_clear();

    volatile int pos = 5;
    volatile int size = strlen(string);

    volatile int i = 0;

    for (i = 0; i < size; i++){
        lcd_writeChar(pos, string[i]);
        if(string[i] != '.') {
            --pos;
        }
        if(pos < 0) {
            return;
        }
    }

}


