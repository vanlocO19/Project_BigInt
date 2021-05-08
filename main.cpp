#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "BigInt.h"
#include "BigInt_core.h"
#include "BigInt_function.h"
#include "BigInt_operator.h"
using namespace std;

int main()
{
	/*char t[] {"100001110101"};

	BI temp = binaryToBigInt(t);

	cout << getLength(temp) << endl;

	char *x = (bigIntToBinary(abs(get2Complement(temp))));
	cout << strlen(x) << endl;
	cout << x;


	*/
	char t[] {"11000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"};
	char s[] {"10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"};
	BI tempA = binaryToBigInt(t);
	BI tempB = binaryToBigInt(s);
	BI A2 = get2Complement(tempA);
	BI B2 = get2Complement(tempB);
	cout << bigIntToBinary(A2) << "\n";
	cout << bigIntToBinary(B2);
	
	
	return 0;
}