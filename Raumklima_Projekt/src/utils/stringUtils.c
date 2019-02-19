#include "stringUtils.h"

void doubleToString(double floatingNumber, char * floatString, int decimals) {
    char tempFloatString[7];
    int tempIndex = 0;
    int index = 0;
    int tempValue = 0;

    tempValue = (int)floatingNumber;
    floatingNumber -= tempValue;

    if (tempValue < 0)
    {
        tempFloatString[index++] = '-';
        tempValue = -tempValue;
    }
    do
    {
        tempFloatString[tempIndex++] = tempValue%10 + '0';
    }
    while( (tempValue /= 10) > 0);

    tempIndex--;

    while(tempIndex > -1)
    {
        floatString[index++] = tempFloatString[tempIndex--];
    }

    floatString[index] = '.';
    tempValue = (int)(floatingNumber * (float)pow(10,decimals));

    tempIndex = index;

    index += decimals;
    floatString[index + 1] = '\0';

    while(index > tempIndex)
    {
        floatString[index--] = tempValue % 10 + '0';
        tempValue /= 10;
    }

}

void floatToString(float floatingNumber, char * floatString, int decimals) {
    char tempFloatString[7];
    int tempIndex = 0;
    int index = 0;
    int tempValue = 0;

    tempValue = (int)floatingNumber;
    floatingNumber -= tempValue;

    if (tempValue < 0)
    {
        tempFloatString[index++] = '-';
        tempValue = -tempValue;
    }
    do
    {
        tempFloatString[tempIndex++] = tempValue%10 + '0';
    }
    while( (tempValue /= 10) > 0);

    tempIndex--;

    while(tempIndex > -1)
    {
        floatString[index++] = tempFloatString[tempIndex--];
    }

    floatString[index] = '.';
    tempValue = (int)(floatingNumber * (float)pow(10,decimals));

    tempIndex = index;

    index += decimals;
    floatString[index + 1] = '\0';

    while(index > tempIndex)
    {
        floatString[index--] = tempValue % 10 + '0';
        tempValue /= 10;
    }

}

void intToString(int integer, char * integerString)
{
    char tempIntegerString[6];
    int tempIndex = 0;
    int index = 0;

    if (integer < 0)
    {
        integerString[index++] = '-';
        integer = -integer;
    }
    do
    {
        tempIntegerString[tempIndex++] = integer%10 + '0';
    }
    while( (integer /= 10) > 0);

    tempIndex--;

    while(tempIndex > -1)
    {
        integerString[index++] = tempIntegerString[tempIndex--];
    }
    integerString[index] = '\0';

}

void removeNullCharacter(char* buffer, int size) {
    int i;

    for(i = 0; i < size; i++) {
        if(buffer[i] == '\x00') {
            buffer[i] = ' ';
        }
    }
}
