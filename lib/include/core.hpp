#pragma once


#ifdef CTEX_STATIC
	#define CTEX_CORE
#elif defined(CTEX_SHARED)
	#ifdef CTEX_WINDOWS
		#ifdef CTEX_BUILD_LIB
			#define CTEX_CORE __declspec(dllexport)
		#else
			#define CTEX_CORE __declspec(dllimport)
		#endif
	#else
		#define CTEX_CORE
	#endif
#else
	#error You must define either 'CTEX_STATIC' or 'CTEX_SHARED'
#endif