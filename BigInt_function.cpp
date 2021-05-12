#include "BigInt_function.h"
#include "BigInt_operator.h"
#include <conio.h>
#include <memory>
#include <string>
#include <algorithm>

BI abs(BI x) // Passed
{
	if (isPositive(x))
		return x;
	else 
		return get2Complement(x);
}

void shiftRBytes(BI& s, int n)
{
	if (n >= s.nBytes) { // Shift all!
		for (int i = 0; i < s.nBytes; i++)
			s.data[i] = 0;
		s.nBytes = 16;
		realloc(s.data, s.nBytes * sizeof(char));
		return;
	}

	int i = 0;

	for (; i < s.nBytes - n; i++) {
		s.data[i] = s.data[i + n];
	}
	normalizeSize(s);

}

void shiftLBytes(BI& s, int n) {
	if (realloc(s.data, (s.nBytes + n) * sizeof(char)) == nullptr) {
		return;
	}
	s.nBytes += n;
	for (int i = s.nBytes - 1; i >= n; i--) {
		s.data[i] = s.data[i - n];
	}
	for (int i = 0; i < n; i++) {
		s.data[i] = 0;
	}
}

void normalizeSize(BI& s) {
	int i = 0;
	for (i = s.nBytes - 1; i >= 0; i--) {
		if (s.data[i] != 0)
			break;
	}
	if (i < 16) {
		s.nBytes = 16;
		realloc(s.data, s.nBytes * sizeof(char));
	} else {
		s.nBytes = i + 1;
		realloc(s.data, s.nBytes * sizeof(char));
	}
}

std::string removeLeadingZeros(std::string s) {
	unsigned int i = 0;
	while (i < s.length() && s[i] == '0') i++;
	if (i == s.length()) return "0"; // Full 0
	return s.substr(i, std::string::npos);
}

int getIthDigit(BI x, int i) {
	if (i < x.nBytes) {
		return x.data[i];
	}
	else {
		return 0;
	}
}

BI get2Complement(BI x) // Passed
{
	BI temp = { 0,0 };
	temp = ~x;
	char carry = 0;
	int sum = 0;

	sum = (int)temp.data[0] + (int)carry + 1;
	if (sum >= 256) {
		carry = sum / 256;
		sum %= 256;
	}
	temp.data[0] = (BYTE)sum;

	for (int i = 1; i < temp.nBytes; i++) {
		sum = (int)temp.data[i] + (int)carry;
		if (sum >= 256) {
			carry = sum / 256;
			sum %= 256;
		}
		temp.data[i] = (BYTE)sum;
	}
	return temp;
}

bool isPositive(BI x) // Passed
{
	return !(x.data[x.nBytes - 1] >> 7);
}

BI binaryToBigInt(char *str) // Passed
{
	int cnt = 0;
	int pos = 0;
	BI temp;
	if (strlen(str) > 128) {
		temp.nBytes = ceil(strlen(str) / 8.f);
	} else {
		temp.nBytes = 16;
	}

	//temp.nBytes++;

	temp.data = (BYTE*)calloc(temp.nBytes, sizeof(BYTE));

	for (int i = strlen(str) - 1; i >= 0; i--) {
		if (cnt == 8) {
			cnt = 0;
			pos++;
		}
		temp.data[pos] += (str[i] == '1') ? (1 << cnt) : 0;
		cnt++;
	}
	return temp;
}




void divide256(std::string s, std::string& quotient, int& remainder) {
	quotient = "0";
	remainder = 0;
	if (s.length() == 0) {
		return;
	}
	if (s.length() < 3) {
		quotient = "0";
		remainder = stoi(s);
		return;
	}
	unsigned int i = 2;
	string temp = s.substr(0, 2);

	// 256 -> max 256 * 9 = 2304

	int val = 0;
	int div = 0;

	while (i < s.length()) {
		temp += s[i];
		val = stoi(temp);
		div = val / 256;
		quotient += to_string(div);
		remainder = val - div * 256;
		temp = to_string(remainder);
		if (temp == "0") temp = "";
		i++;
	}
	quotient = removeLeadingZeros(quotient);
}

BI decimalToBigInt(std::string str)
{
	bool sign = false;
	if (str[0] == '-') {
		sign = true;
		str = str.substr(1, std::string::npos);
	}

	int expected_len = log(str.length()) / log(256) + 1; // Number of bits
	int nBytes = ceil(expected_len / 8.f);
	BI res;
	initBI(nBytes > 16 ? nBytes : 16, res);

	string quotient = "";
	int remainder = 0;
	int i = 0;
	while (str.length() > 0 && str != "0") {
		divide256(str, quotient, remainder);
		res.data[i] = remainder;
		str = quotient;
		i++;
	}

	if (sign)
		res = get2Complement(res);

	return res;
}

std::string bigIntToDecimal(BI x)
{
	std::string res = "0";
	bool sign = !isPositive(x);
	if (sign) {
		x = get2Complement(x);
	}
	for (unsigned int i = 0; i < x.nBytes; i++) {
		res = addDecimal(res, multiplyDecimal(std::to_string(x.data[i]), pow("256", i)));
	}
	res = removeLeadingZeros(res);
	if (sign) return "-" + res;
	else return res;

}

char * bigIntToBinary(BI x) // Passed
{
	char* str = nullptr;
	int n = getLength(x);
	str = (char*)calloc(x.nBytes * 8 + 1, sizeof(char));
	if (str == nullptr) return nullptr;

	int j = 0;
	// First part
	int num = ceil(n / 8.f);
	int bit_first = num * 8 - n;
	bool have_bit_first = false;


	for (int k = 7 - bit_first; k >= 0; k--) {
		str[j] = (x.data[num - 1] & (1 << k)) ? '1' : '0';
		j++;
		have_bit_first = true;
	}

	// The rest
	for (int i = num - 1 - have_bit_first; i >= 0; i--) {
		for (int k = 7; k >= 0; k--) {
			str[j] = (x.data[i] & (1 << k)) ? '1' : '0';
			j++;
		}
	}

	return str;
}



int getLength(BI x) // Passed, return true length
{
	int len = 0;
	int i = x.nBytes - 1;
	while (i >= 0 && x.data[i] == 0) i--;

	for(int k = 7; k >= 0; k--)
		if (x.data[i] & (1 << k))
		{
			len = k + 1;
			break;
		}

	len += i * 8;

	return len;
}

bool initBI(int size, BI& x)
{
	x.nBytes = size;
	x.data = (BYTE*)calloc(size, sizeof(BYTE));
	return !(x.data == nullptr);
}

char * addDecimal(const char *A, const char *B) // backward
{
	char* res = nullptr;
	int len = 0;

	if (strlen(A) > strlen(B))
		len = strlen(A) + 1;
	else
		len = strlen(B) + 1;

	res = (char*)calloc(len + 1, sizeof(char));
	if (res == nullptr) return nullptr;

	char sum = 0;
	char carry = 0;

	for (int i = 0; i < len; i++) {
		if (i < strlen(A))
			sum += A[i] - '0';
		if (i < strlen(B))
			sum += B[i] - '0';
		sum += carry;
		if (sum >= 10) {
			carry = sum / 10;
			sum = sum % 10;
		}
		res[i] = sum + '0';
		sum = 0;
	}
	if (res[len - 1] == '0') {
		res[len - 1] = '\0';
		realloc(res, len);
	}

	return res;
}

std::string addDecimal(std::string A, std::string B, bool rev) // Forward -> outForward
{
	if (A.length() < B.length())
		return addDecimal(B, A, rev);
	if (!rev)
	{
		std::reverse(A.begin(), A.end()); // Flip
		std::reverse(B.begin(), B.end());
	}

	std::string res = "";

	int tempRes = 0;
	int carry = 0;

	while (B.length() < A.length())
		B.push_back('0');
	for (unsigned int i = 0; i < A.length(); i++) {
		tempRes = A[i] - '0' + B[i] - '0' + carry;
		res.push_back(tempRes % 10 + '0');
		carry = tempRes / 10;
	}
	if (carry) res.push_back(carry + '0');
	if(!rev)
		std::reverse(res.begin(), res.end()); // Flip
	return res;
}

char * multiplyDecimal(const char *A, int B) // backward
{
	char* res = nullptr;
	int len = strlen(A) + 1;

	res = (char*)calloc(len + 1, sizeof(char));
	if (res == nullptr) return nullptr;

	int sum = 1;
	char carry = 0;

	for (int i = 0; i < len - 1; i++) {
		sum *= A[i] - '0';
		sum *= B;
		sum += carry;
		if (sum >= 10) {
			carry = sum / 10;
			sum = sum % 10;
		}
		res[i] = sum + '0';
		sum = 1;
	}

	if (carry > 0)
		res[len - 1] = carry + '0';

	if (res[len - 1] == '0') {
		res[len - 1] = '\0';
		realloc(res, len);
	}

	return res;
}

std::string multiplyDecimal(std::string A, std::string B)
{
	if (A.length() < B.length())
		return multiplyDecimal(B, A);

	std::string temp = "";
	std::string res = "";

	int tempRes = 0;
	int carry = 0;

	std::reverse(A.begin(), A.end());
	std::reverse(B.begin(), B.end());

	for (unsigned int i = 0; i < B.length(); i++) {
		for (unsigned int j = 0; j < i; j++) {
			temp.push_back('0');
		}
		for (unsigned int j = i; j < A.length() + i; j++) {
			tempRes = (A[j - i] - '0') * (B[i] - '0') + carry;
			temp.push_back(tempRes % 10 + '0');
			carry = tempRes / 10;
		}
		if (carry) temp.push_back(carry + '0');
		res = addDecimal(res, temp, true);
		temp.erase();
		carry = 0;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::string pow(std::string s, int n)
{
	if (n == 0) {
		return "1";
	} 
	if (n == 1) {
		return s;
	}
	std::string temp = pow(s, n / 2);
	if (n % 2 == 0) {
		return multiplyDecimal(temp, temp);
	} else {
		return multiplyDecimal(temp, multiplyDecimal(temp, s));
	}
}



char * multiplyDecimal(const char *A, const char *B) // backward
{

	if (strlen(A) < strlen(B))
		return multiplyDecimal(B, A);

	char* t = (char*)calloc(strlen(A) + strlen(B) + 1, sizeof(char));
	char* res = (char*)calloc(strlen(A) + strlen(B) + 1, sizeof(char));
	int len = 0;

	/*
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
		BI temp = { nBytesA + nBytesB,tempData };
		BI t = res + temp;
		res = t;
	}
	*/

	int tempRes = 0;
	int carry = 0;

	char* x = nullptr;

	for (int i = 0; i < strlen(B); i++) {
		for (int j = 0; j < i; j++)
			t[j] = '0';
		for (int j = i; j < strlen(A) + i; j++) {
			tempRes = (A[j - i] - '0') * (B[i] - '0') + carry;
			t[j] = tempRes % 10 + '0';
			carry = tempRes / 10;
		}
		if (carry) t[strlen(A) + i] = carry + '0';
		
		res = addDecimal(res, t);

	}
	
	return res;
}

