#pragma once


#ifdef __cplusplus
	extern "C" {
#endif


#define C23_VERSION 202311L

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < C23_VERSION)

	typedef enum {
		CTEX_TRUE = 1,
		CTEX_FALSE = 0
	} CTEX_Bool;

#else

	typedef bool CTEX_Bool;
	#define CTEX_TRUE true
	#define CTEX_FALSE false

#endif // !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < C23_VERSION)


#ifdef __cplusplus
	}
#endif