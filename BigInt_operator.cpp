#include "BigInt_core.h"
#include "BigInt_operator.h"
#include "BigInt_function.h"
#include "BigInt.h"

void assignOperator(BI src, BI& dest) {
	freeBI(dest);
	dest.nBytes = src.nBytes;
	dest.data = (BYTE*)calloc(src.nBytes, sizeof(BYTE));
	memcpy(dest.data, src.data, src.nBytes);
} // Already



BI operator~(BI x)
{
	BI temp = x;
	for (int i = 0; i < temp.nBytes; i++)
		temp.data[i] = ~temp.data[i];
	return temp;
}

BI operator&(const BI &A, const BI &B)
{
	return BI();
}

BI operator|(const BI &A, const BI &B)
{
	return BI();
}

BI operator^(const BI &A, const BI &B)
{
	return BI();
}

BI addOperator(const BI& A, const BI& B) {
	BI res{ 0, nullptr };
	int n;
	if (A.nBytes >= B.nBytes) {
		n = A.nBytes;
	}
	else {
		n = B.nBytes;
	}
	BYTE* tempData = (BYTE*)calloc(n + 1, sizeof(BYTE));
	int tempRes, carry = 0;
	for (int i = 0; i < n; i++) {
		tempRes = (int)getIthDigit(A, i) + (int)getIthDigit(B, i) + (int)carry;
		tempData[i] = tempRes % 256;
		carry = tempRes / 256;
	}
	if (carry != 0) {
		tempData[n] = carry;
		n++;
	}
	res = { n,tempData };
	return res;
}

BI & operator+(const BI &A, const BI &B) // WIP
{
	BI res{ 0, nullptr };
	int n;

	// initBI();

	if (isPositive(A) && isPositive(B)) { // First case: 2 positive - possibility have more bytes
		res = addOperator(A, B);
		
		return res;
	}

	if (!isPositive(A) && !isPositive(B)) { // 2 negative - possibility have more bytes
		BI subA = get2Complement(A);
		BI subB = get2Complement(B);
		res = addOperator(subA, subB);
		if (getLength(res) % 8 == 0) {
			res.nBytes++;
		}
		res = get2Complement(res);
		return res;
	}

	// 1 positive & 1 negative - impossible to have more bytes !
	
	return res;
}

BI & operator-(const BI &A, const BI &B)
{
	BI res;
	return res;
}

BI & operator*(const BI &A, const BI &B)
{
	BI res;
	return res;
}

BI & operator/(const BI &A, const BI &B)
{
	BI res;
	return res;
}

BI & operator%(const BI &A, const BI &B)
{
	BI res;
	return res;
}

