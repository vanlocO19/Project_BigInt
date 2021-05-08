#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "BigInt.h"
#include "BigInt_core.h"
#include "BigInt_function.h"
#include "BigInt_operator.h"
using namespace std;

int main()
{
	char t[]{ "11000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" };


	/*BI temp = binaryToBigInt(t);

	cout << getLength(temp) << endl;

	char *x = (bigIntToBinary(abs(get2Complement(temp))));
	cout << strlen(x) << endl;
	cout << x;*/

	char a[]{ "152634" };
	char b[]{ "12632" };

	//cout << addDecimal(a, b) << endl;

	//cout << multiplyDecimal(a, 4);
	BI x = binaryToBigInt(t);
	char* y = bigIntToBinary(get2Complement(x));

	cout << y;

	
	
	return 0;
}