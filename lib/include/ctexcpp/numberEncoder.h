#pragma once

#include <stdint.h>


#ifdef __cplusplus
	extern "C" {
#endif

#define CTEX_MAX_64_ENCODED_STRING_SIZE 64


const char *CTEX_EncodeNumberToBase64(uint64_t number);


#ifdef __cplusplus
	}
#endif