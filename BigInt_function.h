/*2's complement*/

#include "BigInt_core.h"
#include <memory>

BI abs(BI);
int getIthDigit(BI x, int i);
BI get2Complement(BI);
bool isPositive(BI);
int getLength(BI);

BI binaryToBigInt(string);
BI decimalToBigInt(std::string);
string bigIntToBinary(BI);
string bigIntToDecimal(BI);

bool initBI(int, BI&);

string addDecimal(string, string, bool rev = false);
string mulDecimal(string, string);
string pow(std::string, int);

void shiftRBytes(BI&, int);
void shiftLBytes(BI&, int);

void normalizeSize(BI& s);

