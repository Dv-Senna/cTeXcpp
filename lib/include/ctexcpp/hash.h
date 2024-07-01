#pragma once

#include <stdint.h>


#ifdef __cplusplus
	extern "C" {
#endif


typedef uint64_t CTEX_Hash;

CTEX_Hash CTEX_HashString(const char *str);


#ifdef __cplusplus
	}
#endif