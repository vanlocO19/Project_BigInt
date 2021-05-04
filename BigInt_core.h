#pragma once

#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

typedef unsigned char BYTE;

typedef struct BigInt {
	int nBytes;
	BYTE* data;

	BigInt& operator=(const BigInt&);

} BI;

