#pragma once


#ifdef __cplusplus
	extern "C" {
#endif


typedef enum {
	CTEX_RESULT_SUCCESS = 0,
	CTEX_RESULT_FAILURE,
	CTEX_RESULT_TOO_BIG_STRING,
	CTEX_RESULT_INVALID_ARGUMENT,
	CTEX_RESULT_FAILED_ALLOCATION
} CTEX_Result;


#ifdef __cplusplus
	}
#endif