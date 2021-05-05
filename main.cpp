#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "BigInt.h"
#include "BigInt_core.h"
#include "BigInt_function.h"
#include "BigInt_operator.h"
using namespace std;

int main()
{
	char t[] {"100001110101"};
	char *x = bigIntToBinary(binaryToBigInt(t));
	cout << strlen(x) << endl;
	for (int i = 0; i < 128; i++)
		cout << x[i];
	
	return 0;
}