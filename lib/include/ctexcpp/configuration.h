#pragma once

#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


CTEX_Result CTEX_SetLaTeXPreambule(const char *preambule);
const char *CTEX_GetLaTeXPreambule();

CTEX_Result CTEX_SetBuildFolder(const char *folder);
const char *CTEX_GetBuildFolder();

void CTEX_FreeConfiguration();


#ifdef __cplusplus
	}
#endif