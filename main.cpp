#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "BigInt.h"
#include "BigInt_core.h"
#include "BigInt_function.h"
#include "BigInt_operator.h"
using namespace std;

int main()
{
	//char t[]{"11010"};
	

	/*BI temp = binaryToBigInt(t);

	cout << getLength(temp) << endl;

	char *x = (bigIntToBinary(abs(get2Complement(temp))));
	cout << strlen(x) << endl;
	cout << x;*/

	

	//cout << addDecimal(a, b) << endl;

	//cout << multiplyDecimal(a, 4);
	//BI x = binaryToBigInt(t);
	
	//BI res = x * y;
	//cout << bigIntToBinary(res);

	
	char t[]{ "10100101" };

	BI y = binaryToBigInt(t);
	
	BI x = y << 2;

	cout << bigIntToBinary(y) << endl;

	return 0;
}