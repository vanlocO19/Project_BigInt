/*2's complement*/

#include "BigInt_core.h"
#include <memory>

BI abs(BI);
int getIthDigit(BI x, int i);
BI get2Complement(BI);
bool isPositive(BI);
BI binaryToBigInt(char*);
BI decimalToBigInt(std::string);
std::string bigIntToDecimal(BI);
char* bigIntToBinary(BI);
int getLength(BI);

bool initBI(int, BI&);

//char* addDecimal(const char*, const char*);
std::string addDecimal(std::string, std::string, bool rev = false);

char* multiplyDecimal(const char*, int);
std::string multiplyDecimal(std::string, std::string);

//char* multiplyDecimal(const char*, const char*);


char* divideDecimal(const char*, const int);

std::string pow(std::string, int);