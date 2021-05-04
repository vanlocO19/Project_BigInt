#pragma once

#include <stdio.h>
#include <iostream>

using namespace std;

typedef unsigned char BYTE;
typedef struct BigInt {
	int nBytes;
	BYTE* data;
} BI;

