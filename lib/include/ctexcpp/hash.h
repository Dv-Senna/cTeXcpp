#pragma once

#include <stdint.h>


#ifdef __cplusplus
	extern "C" {
#endif


typedef uint64_t CTEX_Hash;

/**
 * @brief Hash a string into an uint64_t hash. Don't use it for cryptographic purposes
 */
CTEX_Hash CTEX_HashString(const char *str);


#ifdef __cplusplus
	}
#endif