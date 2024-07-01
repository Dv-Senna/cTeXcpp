#pragma once

#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


CTEX_Result CTEX_SetLaTeXPreambule(const char *preambule);
const char *CTEX_GetLaTeXPreambule();


#ifdef __cplusplus
	}
#endif