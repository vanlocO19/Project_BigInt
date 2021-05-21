#include "BigInt_function.h"
#include "BigInt_operator.h"
#include <conio.h>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

std::string removeLeadingZeros(std::string s) {
	unsigned int i = 0;
	while (i < s.length() && s[i] == '0') i++;
	if (i == s.length()) return "0"; // Full 0
	return s.substr(i, std::string::npos);
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

BI abs(BI x) // Passed
{
	if (isPositive(x))
		return x;
	else 
		return get2Complement(x);
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
	BI temp;
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
	return move(temp);
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
bool isPositive(BI x) // Passed
{
	return !(x.data[x.nBytes - 1] >> 7);
}

BI binaryToBigInt(string str) // Passed
{
	int cnt = 0;
	int pos = 0;
	BI temp;
	if (str.length() > 128) {
		temp.nBytes = ceil(str.length() / 8.f);
	} else {
		temp.nBytes = 16;
	}
	temp.cap = temp.nBytes + 8;

	temp.data = (BYTE*)calloc(temp.cap, 1);

	for (int i = str.length() - 1; i >= 0; i--) {
		if (cnt == 8) {
			cnt = 0;
			pos++;
		}
		temp.data[pos] += (str[i] == '1') ? (1 << cnt) : 0;
		cnt++;
	}
	return move(temp);
}
BI decimalToBigInt(string str)
{
	bool sign = false;
	if (str[0] == '-') {
		sign = true;
		str = str.substr(1, std::string::npos);
	}

	int nBytes = ceil((str.length() + 1) / log(256));
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

	return move(res);
}
string bigIntToBinary(BI x) // Passed
{
	string str = "";
	int n = getLength(x);

	int j = 0;
	// First part
	int num = ceil(n / 8.f);
	int bit_first = num * 8 - n;
	bool have_bit_first = false;


	for (int k = 7 - bit_first; k >= 0; k--) {
		str += (x.data[num - 1] & (1 << k)) ? '1' : '0';
		j++;
		have_bit_first = true;
	}

	// The rest
	for (int i = num - 1 - have_bit_first; i >= 0; i--) {
		for (int k = 7; k >= 0; k--) {
			str += (x.data[i] & (1 << k)) ? '1' : '0';
			j++;
		}
	}

	return str;
}
string bigIntToDecimal(BI x)
{
	string res = "0";
	bool sign = !isPositive(x);
	if (sign) {
		x = get2Complement(x);
	}
	for (int i = 0; i < x.nBytes; i++) {
		res = addDecimal(res, mulDecimal(to_string(x.data[i]), pow("256", i)));
	}
	res = removeLeadingZeros(res);
	if (sign) return "-" + res;
	return res;
}

bool initBI(int size, BI& x)
{
	x.cap = size + 8;
	x.nBytes = size;
	x.data = (BYTE*)calloc(size, sizeof(BYTE));
	return !(x.data == nullptr);
}

string addDecimal(string A, string B, bool rev) // Forward -> outForward
{
	if (A.length() < B.length())
		return addDecimal(B, A, rev);
	if (!rev)
	{
		reverse(A.begin(), A.end()); // Flip
		reverse(B.begin(), B.end());
	}

	string res = "";

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
		reverse(res.begin(), res.end()); // Flip
	return res;
}
string mulDecimal(string A, string B)
{
	if (A.length() < B.length())
		return mulDecimal(B, A);

	string temp = "";
	std::string res = "";

	int tempRes = 0;
	int carry = 0;

	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

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
	reverse(res.begin(), res.end());
	return res;
}
string pow(string s, int n)
{
	if (n == 0) {
		return "1";
	} 
	if (n == 1) {
		return s;
	}
	std::string temp = pow(s, n / 2);
	if (n % 2 == 0) {
		return mulDecimal(temp, temp);
	} 
	return mulDecimal(temp, mulDecimal(temp, s));
}

void shiftLBytes(BI& s, int n) {
	if(s.nBytes + n > s.cap)
		if ((s.data = (BYTE*)realloc(s.data, (s.nBytes + n))) == nullptr)
			return;
	
	s.nBytes += n;
	for (int i = s.nBytes - 1; i >= n; i--) {
		s.data[i] = s.data[i - n];
	}
	for (int i = 0; i < n; i++) {
		s.data[i] = 0;
	}
}
void shiftRBytes(BI& s, int n)
{
	if (n >= s.nBytes) { // Shift all!
		for (int i = 0; i < s.nBytes; i++)
			s.data[i] = 0;
		s.cap = 16 + 8;
		s.nBytes = 16;
		if ((s.data = (BYTE*)realloc(s.data, (s.nBytes + n))) == nullptr)
			return;
		return;
	}

	int i = 0;
	for (; i < s.nBytes - n; i++) {
		s.data[i] = s.data[i + n];
	}
	normalizeSize(s);
}

void normalizeSize(BI& s) {
	int i = 0;
	for (i = s.nBytes - 1; i >= 0; i--) {
		if (s.data[i] != 0)
			break;
	}
	if (i < 16) {
		s.nBytes = 16;
	} else {
		s.nBytes = i + 1;
	}
}

BI min(const BI& A, const BI& B) {
	BI res;
	BI difference = A - B;
	if (isPositive(difference)) {
		res = B;
	}
	else {
		res = A;
	}
	return res;
}

BI max(const BI& A, const BI& B) {
	BI res;
	BI difference = A - B;
	if (isPositive(difference)) {
		res = A;
	}
	else {
		res = B;
	}
	return res;
}

bool isEven(BI A) {
	int last = A.data[0];
	if (last % 2 == 0) {
		return true;
	}
	return false;
}

BI pow(const BI& A, const BI& B) {
	BI one = decimalToBigInt("1");
	if (getLength(B - one) == 0) {
		return A;
	}
	BI two = decimalToBigInt("2");
	BI temp = pow(A, B / two);
	if (isEven(B)) {
		return temp * temp;
	}
	return temp * temp * A;
}

int digits(const BI& A) {
	return getLength(A);
}

string to_string(const BI& A) {
	string res;
	return res;
}

string to_base32(const BI& A) {
	string str32 = "32";
	BI thiryTwo = decimalToBigInt(str32);
	int sign = !isPositive(A);
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	string res;
	string subString;
	int index;
	BI subA = A;
	while (getLength(subA) > 0) {
		subString = bigIntToDecimal(subA % thiryTwo);
		if (subString.length() == 1) {
			index = subString[0] - '0';
		}
		else {
			index = subString[1] - '0' + (subString[0] - '0') * 10;
		}
		res += alphabet[index];
		subA = subA / thiryTwo;
	}

	std::reverse(res.begin(), res.end());
	if (sign) {
		return "-" + res;
	}
	return res;
}

string to_base58(const BI& A) {
	string str58 = "58";
	BI fiftyEight = decimalToBigInt(str58);
	int sign = !isPositive(A);
	string alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	string res;
	string subString;
	int index;
	BI subA(A);
	while (getLength(subA) > 0) {
		subString = bigIntToDecimal(subA % fiftyEight);
		if (subString.length() == 1) {
			index = subString[0] - '0';
		}
		else {
			index = subString[1] - '0' + (subString[0] - '0') * 10;
		}
		res += alphabet[index];
		subA = subA / fiftyEight;
	}

	std::reverse(res.begin(), res.end());
	if (sign) {
		return "-" + res;
	}
	return res;
}

string to_base64(const BI& A) {
	string str64 = "64";
	BI sixtyFour = decimalToBigInt(str64);
	int sign = !isPositive(A);
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string res;
	string subString;
	int index;
	BI subA = A;
	while (getLength(subA) > 0) {
		subString = bigIntToDecimal(subA % sixtyFour);
		if (subString.length() == 1) {
			index = subString[0] - '0';
		}
		else {
			index = subString[1] - '0' + (subString[0] - '0') * 10;
		}
		res += alphabet[index];
		subA = subA / sixtyFour;
	}

	std::reverse(res.begin(), res.end());
	if (sign) {
		return "-" + res;
	}
	return res;
}

bool is_prime(const BI& A) {
	bool res = false;
	return res;
}
