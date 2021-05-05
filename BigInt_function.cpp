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
	return ~(x.data[x.nBytes - 1] >> 7);
}

BI binaryToBigInt(char *str)
{
	int cnt = 0;
	int pos = 0;
	BI temp;
	if (strlen(str) > 128) {
		temp.nBytes = (strlen(str) / 8);
	} else {
		temp.nBytes = 16;
	}

	temp.data = (BYTE*)malloc(temp.nBytes * sizeof(BYTE));

	memset(temp.data, 0, sizeof(temp.data));

	for (int i = strlen(str) - 1; i >= 0; i--) {
		if (cnt < 8) {
			temp.data[pos] += (str[i] == '1') ? (1 << cnt) : 0;
			cnt++;
		} else {
			cnt = 0;
			pos++;
		}
	}
	return temp;
}

BI decimalToBigInt(char *str)
{
	return BI();
}

char * bigIntToDecimal(BI x)
{
	return nullptr;
}

char * bigIntToBinary(BI x)
{
	char* str = nullptr;
	int n = getLength(x);
	str = (char*)malloc((n + 1) * sizeof(char));
	if (str == nullptr) return nullptr;
	
	str[n] = '\0';

	// Set first "digit"

	int f_len = n - 8 * (x.nBytes - 1);
	int j = 0;
	for (int i = f_len - 1; i >= 0; i--) {
		str[j] = (x.data[x.nBytes - 1] & (1 << i)) ? '1' : '0';
		j++;
	}

	// 00110010 -> f_len = 6,
	// 00110010 & 00100000 <=> 00110010 & (1 << 5) <=> 1

	for (int i = x.nBytes - 2; i >= 0; i--) {
		for (int k = 7; k >= 0; k--) {
			str[j] = (x.data[i] & (1 << k)) ? '1' : '0';
			j++;
		}
	}

	return str;
}

int getLength(BI x)
{
	int len = 0;
	for(int i = 7; i >= 0; i--)
		if (x.data[x.nBytes - 1] & (1 << i)) {
			len = i;
			break;
		}
	len += (x.nBytes - 1) * 8;

	return len;
}
