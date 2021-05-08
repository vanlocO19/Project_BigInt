#include "BigInt_core.h"

BigInt & BigInt::operator=(const BigInt & other)
{
	if (this == &other)
		return *this;
	if (nBytes != other.nBytes) {
		if(data != nullptr)
			free(data);
		data = nullptr;
		nBytes = other.nBytes;
		data = (BYTE*)malloc(nBytes * sizeof(BYTE));
	}
	memcpy(data, other.data, nBytes * sizeof(BYTE));
	return *this;
}
