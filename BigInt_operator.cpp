#include "BigInt_core.h"
#include "BigInt_operator.h"
#include "BigInt_function.h"
#include "BigInt.h"

#include <iostream>
#include <string>
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
	initBI(16, res);
	BYTE* tempData = nullptr;
	int nBytesA = ceil(getLength(A) / 8.f);
	int nBytesB = ceil(getLength(B) / 8.f);

	temp.nBytes = (nBytesA + nBytesB > 16 ? nBytesA + nBytesB : 16);
	temp.cap = temp.nBytes + 8;
	temp.data = (BYTE*)calloc(temp.cap, 1);

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
		//return move(res);
	}
	//normalizeSize(res);
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
	/*OKAY PLEASE MAKE THIS CODE CLEARLY LATER.*/
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

		BI dividend(A);
		BI divisor(B);

		int k = getLength(A) + getLength(B);
		BI x = dividend - divisor;
		BI lastx;
		initBI(16, lastx);
		BI one = decimalToBigInt("1");
		BI pow2 = one << (k + 1);
		//cout << bigIntToDecimal(pow2) << endl;

		

		while (getLength(x - lastx) > 0) {
			lastx = x;
			x = (x * (pow2 - x * divisor)) >> k;
			//cout << bigIntToDecimal(x) << endl;
		}

		/*if (!isPositive(x * divisor - pow2 >> 1) || getLength(x  *divisor - pow2 >> 1) == 0) {
			x = x + decimalToBigInt("1");
		}
		*/

		BI quotient = (dividend * x) >> k;

		BI temp = dividend - quotient * divisor - divisor;
		if (isPositive(temp) || getLength(temp) == 0) {
			quotient = quotient + decimalToBigInt("1");
		}

		res = quotient;

		//res = (dividend * x) >> k;

		return move(res);
	}
}

BI operator%(const BI &A, const BI &B)
{
	BI remainder = A;
	BI divisor = B;
	/*BI quotient = A / B;
	BI remainder = A - B * quotient;
	*/
	
	while (isPositive(remainder - divisor)) {
		remainder = remainder - divisor;
	}
	
	if (getLength(remainder - divisor) == 0) {
		remainder = decimalToBigInt("0");
	}

	BI res = remainder;
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
		normalizeSize(res);
		if (getLength(res) % 8 == 0)
			res.nBytes++;
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

	normalizeSize(res);
	if (getLength(res) % 8 == 0)
		res.nBytes++;

	if (sign) res = get2Complement(res);

	return move(res);
}

