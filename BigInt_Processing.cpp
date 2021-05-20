#include "BigInt.h"
#include "BigInt_core.h"
#include "BigInt_function.h"
#include "BigInt_operator.h"
#include "BigInt_Processing.h"

BI processWhenNIsFour(char* parameter[], BI para1, BI para2, FILE* fo) {
	BI res;
	initBI(16, res);
	char* toCmp = parameter[2];
	if (strcmp(toCmp, "+") == 0) {
		res = para1 + para2;
	}
	else if (strcmp(toCmp, "-") == 0) {
		res = para1 - para2;
	}
	else if (strcmp(toCmp, "*") == 0) {
		res = para1 * para2;
	}
	else if (strcmp(toCmp, "/") == 0) {
		res = para1 / para2;
	}
	else if (strcmp(toCmp, "%") == 0) {
		res = para1 % para2;
	}
	else if (strcmp(toCmp, "&") == 0) {
		res = para1 & para2;
	}
	else if (strcmp(toCmp, "|") == 0) {
		res = para1 | para2;
	}
	else if (strcmp(toCmp, "^") == 0) {
		res = para1 ^ para2;
	}
	else {
		int toShift = 0;
		int len = strlen(parameter[3]);
		for (int i = len - 1; i >= 0; i--) {
			toShift = toShift * 10 + parameter[3][i];
		}
		if (strcmp(toCmp, ">>") == 0) {
			res = para1 >> toShift;
		}
		else {
			res = para1 << toShift;
		}
	}
	return res;
}



void BIProcess(int n, char* parameter[], FILE* fo) {
	if (n == 3) {
		if (strcmp(parameter[1], "~") == 0) {
			BI para;
			BI res;
			if (strcmp(parameter[0], "2") == 0){
				para = binaryToBigInt(parameter[2]);
				res = ~para;
				fprintf(fo, "%s\n", bigIntToBinary(res));
			}
			else {
				para = decimalToBigInt(parameter[2]);
				res = ~para;
				fprintf(fo, "%s\n", bigIntToDecimal(res));
			}
		}
		else if (strcmp(parameter[0], "2") == 0) {
			BI para;
			para = binaryToBigInt(parameter[2]);
			fprintf(fo, "%s\n", bigIntToDecimal(para));
		}
		else
		{
			BI para;
			para = decimalToBigInt(parameter[2]);
			fprintf(fo, "%s\n", bigIntToBinary(para));
		}
	}
	else {
		BI para1;
		BI para2;
		initBI(16, para1);
		initBI(16, para2);
		BI res;
		initBI(16, res);
		if (strcmp(parameter[0], "2") == 0) {
			para1 = binaryToBigInt(parameter[1]);
			para2 = binaryToBigInt(parameter[3]);
			res = processWhenNIsFour(parameter, para1, para2, fo);
			fprintf(fo, "%s\n", bigIntToBinary(res));
		}
		else {
			para1 = decimalToBigInt(parameter[1]);
			para2 = decimalToBigInt(parameter[3]);
			processWhenNIsFour(parameter, para1, para2, fo);
			fprintf(fo, "%s\n", bigIntToDecimal(res));
		}
	}
}