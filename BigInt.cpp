#include "BigInt.h"

void freeBI(BI& x) {
	free(x.data);
	x.data = NULL;
	x.nBytes = 0;
}