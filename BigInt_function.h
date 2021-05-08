/*2's complement*/

#include "BigInt_core.h"

BI abs(BI);
int getIthDigit(BI x, int i);
BI get2Complement(BI);
bool isPositive(BI);
BI binaryToBigInt(char*);
BI decimalToBigInt(char*);
char* bigIntToDecimal(BI);
char* bigIntToBinary(BI);
int getLength(BI);

bool initBI(int, BI&);