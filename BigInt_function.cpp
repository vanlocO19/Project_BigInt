#include "BigInt_function.h"
#include "BigInt_operator.h"

BI abs(BI x)
{
	if (isPositive(x))
		return x;
	else 
		return get2Complement(x);
}

BI get2Complement(BI x)
{
	BI temp = ~x;
	char carry = 0;
	int sum = 0;
	for (int i = 0; i < temp.nBytes; i++) {
		sum = (int)temp.data[i] + carry + 1;
		if (sum >= 256) {
			sum -= 256;
			carry = 1;
		}
		temp.data[i] = (BYTE)sum;
	}
	return temp;
}

bool isPositive(BI x)
{
	return (x.data[x.nBytes - 1] >> 7) & 1;
}
