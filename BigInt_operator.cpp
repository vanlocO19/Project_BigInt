#include "BigInt_core.h"
#include "BigInt_operator.h"
#include "BigInt_function.h"
#include "BigInt.h"
// abc
void assignOperator(BI src, BI& dest) {
	freeBI(dest);
	dest.nBytes = src.nBytes;
	dest.data = (BYTE*)calloc(src.nBytes, sizeof(BYTE));
	memcpy(dest.data, src.data, src.nBytes);
}

BI addOperator(BI term1, BI term2) {
	int n;
	if (term1.nBytes > term2.nBytes) {
		n = term1.nBytes;
	}
	else {
		n = term2.nBytes;
	}
	BYTE* tempData = (BYTE*)calloc(n + 1, sizeof(BYTE)); //should we check NULL pointer?...
	int tempRes, carry = 0;
	for (int i = 0; i < n; i++) {
		tempRes = term1.data[i] + term2.data[i] + carry;
		tempData[i] = tempRes % 256;
		carry = tempRes / 256;
	}
	if (carry != 0) {
		tempData[n] = carry;
		n++;
	}
	BI res = { n,tempData };
	return res;
}

BI operator~(BI x)
{
	BI temp = x;
	for (int i = 0; i < temp.nBytes; i++)
		temp.data[i] = !temp.data[i];
	return temp;
}

