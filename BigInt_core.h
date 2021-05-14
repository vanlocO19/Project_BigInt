#pragma once

#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

typedef unsigned char BYTE;

typedef struct BigInt {
	int cap;
	int nBytes;
	BYTE* data;

	BigInt();
	BigInt(const BigInt&);

	BigInt& operator=(const BigInt&);

	~BigInt();

} BI;

