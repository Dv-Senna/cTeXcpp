#pragma once

#include <stdint.h>


#ifdef __cplusplus
	extern "C" {
#endif

#define CTEX_MAX_64_ENCODED_STRING_SIZE 64


/**
 * @brief Encode number to base 64 string
 * @warning You must manually free the string using `free(void*)`
 */
const char *CTEX_EncodeNumberToBase64(uint64_t number);


#ifdef __cplusplus
	}
#endif