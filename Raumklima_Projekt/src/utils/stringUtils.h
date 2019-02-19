#ifndef SRC_UTILS_STRINGUTILS_H_
#define SRC_UTILS_STRINGUTILS_H_

#include<math.h>

void doubleToString(double floatingNumber, char * floatString, int decimals);
void floatToString(float floatingNumber, char * floatString, int decimals);
void intToString(int integer,char * integerString);
void removeNullCharacter(char* buffer, int size);

#endif /* SRC_UTILS_STRINGUTILS_H_ */
