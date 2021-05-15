#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <time.h>
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

	
	/*char t[]{ "10100101" };

	BI y = binaryToBigInt(t);
	
	BI x = y >> 4;

	cout << bigIntToBinary(y) << endl;
	cout << bigIntToBinary(x) << "\n";*/

	char t[]{"1000000"};
	char s[]{"100"};
	BI t1 = binaryToBigInt(t);
	BI s1 = binaryToBigInt(s);
	BI res = t1 / s1;
	cout << bigIntToBinary(res) << "\n";

	/*BI t1 = decimalToBigInt("21356");
	BI s1 = decimalToBigInt("2389");*/

	/*cout << bigIntToDecimal(t1) << "\n";
	cout << bigIntToDecimal(s1) << "\n";*/

	//BI res = t1 * s1;
	//cout << bigIntToDecimal(t1) << "\n";
	//cout << bigIntToDecimal(s1) << "\n";
	/*cout << bigIntToDecimal(res) << "\n";
	res = res << 4;
	cout << bigIntToDecimal(res) << "\n";
	res = res >> 2;
	cout << bigIntToDecimal(res) << "\n";
	res = res / s1;
	cout << bigIntToDecimal(res) << "\n";
	
	cerr << endl << "Tick: " << clock() << endl;
	*/return 0;
}