#include "BigInt_core.h"

BigInt::BigInt()
{
	cap = 0;
	nBytes = 0;
	data = nullptr;
}

BigInt::BigInt(const BigInt &other)
{
	cap = other.cap;
	nBytes = other.nBytes;
	data = (BYTE*)calloc(cap, 1);
	memcpy(data, other.data, nBytes);
}

BigInt & BigInt::operator=(const BigInt & other)
{
	if (this == &other)
		return *this;
	if (nBytes != other.nBytes) {
		if(data != nullptr)
			free(data);
		data = nullptr;
		nBytes = other.nBytes;
		cap = other.cap;
		data = (BYTE*)calloc(cap, 1);
	}
	memcpy(data, other.data, nBytes);
	return *this;
}

BigInt::~BigInt()
{
	nBytes = 0;
	cap = 0;
	if(data)
		free(data);
	data = nullptr;
}
