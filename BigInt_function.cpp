#include "BigInt_function.h"
#include "BigInt_operator.h"

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
	BI temp = ~x;
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

BI decimalToBigInt(char *str)
{
	return BI();
}

char * bigIntToDecimal(BI x)
{
	
	// A * 256 ^ 0 + B * 256 ^ 1 + C * 256 ^ 2 ... ^n -> Find way to multiply 2 decimal number
	return nullptr;
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

char * addDecimal(const char *A, const char *B)
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

char * multiplyDecimal(const char *A, int B)
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

char * multiplyDecimal(const char *A, const char *B)
{
	return nullptr;
}
