/*2's complement*/

#include "BigInt_core.h"

BI abs(BI);
BI get2Complement(BI);
bool isPositive(BI);
BI binaryToBigInt(char*);
BI decimalToBigInt(char*);
char* bigIntToDecimal(BI);
char* bigIntToBinary(BI);
int getLength(BI);

bool initBI(int, BI&);

char* addDecimal(const char*, const char*);

char* multiplyDecimal(const char*, int);

char* multiplyDecimal(const char*, const char*);