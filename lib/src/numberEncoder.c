#include "ctexcpp/numberEncoder.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



const char *CTEX_EncodeNumberToBase64(uint64_t number) {
	const char charTable[64] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"};

	size_t outputStringSize = ceil(log2(number) / 6.0);
	char *outputString = malloc(sizeof(char) * (outputStringSize + 1));
	outputString[outputStringSize] = '\0';

	for (int64_t i = outputStringSize - 1; i >= 0; --i) {
		uint64_t base = pow(64, i);
		uint64_t digit = floor(number / (double)base);
		number -= digit * base;
		outputString[outputStringSize - i - 1] = charTable[digit];
	}

	return outputString;
}

