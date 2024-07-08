#pragma once

#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


/**
 * @brief Used to add a custom preambule (for example custom package) to the LaTeX file
 */
CTEX_Result CTEX_SetLaTeXPreambule(const char *preambule);
const char *CTEX_GetLaTeXPreambule();

/**
 * @brief Used to change the build folder of LaTeX. Default value is 'latex'
 */
CTEX_Result CTEX_SetBuildFolder(const char *folder);
const char *CTEX_GetBuildFolder();

/**
 * @brief Used internally by CTEX_Quit()
 */
void CTEX_FreeConfiguration();


#ifdef __cplusplus
	}
#endif