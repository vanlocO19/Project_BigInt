#include "BigInt_core.h"
#include "BigInt_operator.h"
#include "BigInt_function.h"
#include "BigInt.h"

BI operator~(BI x)
{
	BI temp;
	temp = x;
	for (int i = 0; i < temp.nBytes; i++)
		temp.data[i] = ~temp.data[i];
	return move(temp);
}
BI operator&(const BI &A, const BI &B)
{
	BI temp;
	if (getLength(A) < getLength(B)) {
		temp = A;
	} else {
		temp = B;
	}

	for (int i = 0; i < temp.nBytes; i++) {
		temp.data[i] = A.data[i] & B.data[i];
	}

	return move(temp);
}
BI operator|(const BI &A, const BI &B)
{
	BI temp;
	if (getLength(A) > getLength(B)) {
		temp = A;
	} else {
		temp = B;
	}
	for (int i = 0; i < temp.nBytes; i++) {
		temp.data[i] = getIthDigit(A, i) | getIthDigit(B, i);
	}
	return move(temp);
}
BI operator^(const BI &A, const BI &B)
{
	BI temp;
	if (getLength(A) > getLength(B)) {
		temp = A;
	} else {
		temp = B;
	}
	for (int i = 0; i < temp.nBytes; i++) {
		temp.data[i] = getIthDigit(A, i) ^ getIthDigit(B, i);
	}
	return move(temp);
}

BI addOperator(const BI& A, const BI& B, bool chk) {
	BI res;
	int n;
	if (A.nBytes >= B.nBytes) {
		n = A.nBytes;
	}
	else {
		n = B.nBytes;
	}
	res.cap = n + 8;
	res.nBytes = n;
	res.data = (BYTE*)calloc(res.cap, 1);

	BYTE* tempData = res.data;
	int tempRes, carry = 0;
	for (int i = 0; i < n; i++) {
		tempRes = (int)getIthDigit(A, i) + (int)getIthDigit(B, i) + (int)carry;
		tempData[i] = tempRes % 256;
		carry = tempRes / 256;
	}
	if (carry != 0 && chk) {
		tempData[n] = carry;
		n++;
		res.nBytes++;
	}
	return move(res);
}
BI multiOperator(const BI& A, const BI& B) { //in this sub-function, nBytes of A is less than nBytes of B
	BI res;
	BI temp;
	//initBI(16, res);
	BYTE* tempData = nullptr;
	int nBytesA = A.nBytes;
	int nBytesB = B.nBytes;

	temp.cap = nBytesA + nBytesB;
	temp.nBytes = nBytesA + nBytesB;
	temp.data = (BYTE*)calloc(temp.nBytes, 1);

	tempData = temp.data; 

	int tempRes = 0, carry = 0;
	for (int i = 0; i < nBytesA; i++) {
		for (int j = 0; j < i; j++) {
			tempData[j] = 0;
		}
		for (int j = i; j < nBytesB + i; j++) {
			tempRes = (int)A.data[i] * (int)B.data[j - i] + carry;
			tempData[j] = tempRes % 256;
			carry = tempRes / 256;
		}
		if (carry != 0) {
			tempData[nBytesB + i] = carry;
		}
		res = res + temp;
	}
	normalizeSize(res);
	return move(res);
}

BI operator+(const BI &A, const BI &B) // WIP
{
	BI res;
	bool chk = true;

	if (isPositive(A) && isPositive(B)) { // First case: 2 positive - possibility have more bytes
		res = addOperator(A, B, chk);
		return move(res);
	}

	if (!isPositive(A) && !isPositive(B)) { // 2 negative - possibility have more bytes
		BI subA = get2Complement(A);
		BI subB = get2Complement(B);
		res = addOperator(subA, subB, chk);
		if (getLength(res) % 8 == 0) {
			res.nBytes++;
		}
		res = get2Complement(res);
		return move(res);
	}

	// 1 positive & 1 negative - impossible to have more bytes !
	chk = false;
	res = addOperator(A, B, chk);
	normalizeSize(res);
	return move(res);
}
BI operator-(const BI &A, const BI &B)
{
	BI B2 = get2Complement(B);
	BI temp = A + B2;
	return move(temp);
}
BI operator*(const BI &A, const BI &B)
{
	BI res;
	bool aPos = isPositive(A);
	bool bPos = isPositive(B);
	/*I've forgot the abs function... Let me minimalize it later.*/
	if (A.nBytes < B.nBytes) {
		if (aPos && bPos) {
			res = multiOperator(A, B);
		}
		else if (!aPos && !bPos) {
			BI a2 = get2Complement(A);
			BI b2 = get2Complement(B);
			res = multiOperator(a2, b2);
		}
		else {
			BI sub;
			if (!aPos) {
				sub = get2Complement(A);
				res = multiOperator(sub, B);
			}
			else {
				sub = get2Complement(B);
				res = multiOperator(A, sub);
			}
			BI temp = get2Complement(res);
			res = temp;
		}
	}
	else {
		if (aPos && bPos) {
			res = multiOperator(B, A);
		}
		else if (!aPos && !bPos) {
			BI a2 = get2Complement(A);
			BI b2 = get2Complement(B);
			res = multiOperator(b2, a2);
		}
		else {
			BI sub;
			if (!aPos) {
				sub = get2Complement(A);
				res = multiOperator(B, sub);
			}
			else {
				sub = get2Complement(B);
				res = multiOperator(sub, A);
			}
			BI temp = get2Complement(res);
			res = temp;
		}
	}
	return move(res);
}
BI operator/(const BI &A, const BI &B)
{
	BI res;
	if (getLength(B) == 0) {
		printf("Hey bro what are you doing?");
		return res;
	}
	else {
		/*Cre: StackOverflow - Newton-Raphson division*/

		BI dividend;
		dividend = A;
		BI divisor;
		divisor = B;
		int k = getLength(dividend) + getLength(divisor);
		
		char sub[]{"1"};
		BI powOf2 = binaryToBigInt(sub);
		BI temp = powOf2 << (k + 1);
		powOf2 = temp;
		BI one = binaryToBigInt(sub);
		BI x = dividend - divisor;
		BI lastx, lastlastx;
		initBI(16, lastx);
		initBI(16, lastlastx);
		while (true) {
			BI temp1 = x * divisor;
			BI temp11 = powOf2 - temp1;
			BI temp111 = x * temp11;
			BI temp2 = temp111 >> k;
			x = temp2;
			if (getLength(x - lastx) == 0 || getLength(x - lastlastx) == 0) {
				break;
			}
			lastlastx = lastx;
			lastx = x;
			BI temp3 = dividend * x;
			BI temp4 = temp3 >> k;
			BI q;
			q = temp4;
			if (isPositive(dividend - q * divisor - divisor) || getLength(dividend - q * divisor - divisor) == 0) {
				BI temp5 = q + one;
				q = temp5;
			}
			res = q;
		}
		if (isPositive(res * B - A)) {
			BI temp = res - one;
			res = temp;
		}
		return move(res);
	}
	
}
BI operator%(const BI &A, const BI &B)
{
	BI res;
	return move(res);
}

BI operator>>(const BI& A, const int& n)
{
	BI res(A);
	bool sign = false;
	if (!isPositive(A)) {
		res = get2Complement(res);
		sign = true;
	}

	int byte_shift = n / 8;
	int bit_shift = n % 8;
	shiftRBytes(res, byte_shift);
	if (bit_shift > 0) {

		BYTE carry = 0;
		BYTE temp = 0;
		for (int i = res.nBytes - 1; i >= 0; i--) {
			temp = res.data[i];
			res.data[i] = (res.data[i] >> bit_shift) + carry;
			carry = temp << (8 - bit_shift);
			//carry >>= (8 - bit_shift); // overflow trick
		}
	}

	if (getLength(res) >= 128) {
		if (getLength(res) % 8 != 0) {
			normalizeSize(res);
		}
	}

	if (sign) res = get2Complement(res);

	return move(res);
}
BI operator<<(const BI& A, const int& n)
{
	BI res(A);
	
	bool sign = false;
	if (!isPositive(A)) {
		res = get2Complement(res);
		sign = true;
	}
	
	int byte_shift = n / 8;
	int bit_shift = n % 8;
	shiftLBytes(res, byte_shift);
	if (bit_shift > 0) {

		if (getLength(res) + bit_shift >= 128) {
			res.nBytes++;
			realloc(res.data, res.nBytes * sizeof(char));
		}

		int carry = 0;
		int temp = 0;
		for (int i = 0; i < res.nBytes; i++) {
			temp = res.data[i];
			res.data[i] = (res.data[i] << bit_shift) + carry;
			carry = temp >> (8 - bit_shift);
		}
	}

	if (getLength(res) >= 128) {
		if (getLength(res) % 8 != 0) {
			normalizeSize(res);
		}
	}

	if (sign) res = get2Complement(res);

	return move(res);
}

