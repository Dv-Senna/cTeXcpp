#include "ctexcpp/configuration.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ctexcpp/error.h"


char *__CTEX_LaTeXPreambule = NULL;
char *__CTEX_BuildFolder = NULL;

#define COPY_STRING(arg, var) if (arg == NULL) {\
	if (var != NULL)\
		free(var);\
	var = NULL;\
\
	(void)CTEX_PushError("Invalid argument given to `CTEX_SetLaTeXPreambule` : " #arg " must be non-null");\
	return CTEX_RESULT_INVALID_ARGUMENT;\
}\
\
size_t preambuleLength = strlen(arg);\
size_t oldPreambuleLength = 0;\
if (var != NULL)\
	oldPreambuleLength = strlen(var);\
\
if (oldPreambuleLength != preambuleLength) {\
	if (var != NULL)\
		free(var);\
\
	var = (char*)malloc(sizeof(char) * (preambuleLength + 1));\
	if (var == NULL) {\
		(void)CTEX_PushError("Failed allocation in `CTEX_SetLaTeXPreambule` : can't allocate memory to store the new " #arg);\
		return CTEX_RESULT_FAILED_ALLOCATION;\
	}\
}\
\
memcpy(var, arg, preambuleLength);\
var[preambuleLength] = '\0';\
return CTEX_RESULT_SUCCESS



CTEX_Result CTEX_SetLaTeXPreambule(const char *preambule) {
	COPY_STRING(preambule, __CTEX_LaTeXPreambule);
}


const char *CTEX_GetLaTeXPreambule() {
	return __CTEX_LaTeXPreambule;
}


CTEX_Result CTEX_SetBuildFolder(const char *folder) {
	COPY_STRING(folder, __CTEX_BuildFolder);
}


const char *CTEX_GetBuildFolder() {
	return __CTEX_BuildFolder;
}


void CTEX_FreeConfiguration() {
	if (__CTEX_BuildFolder != NULL)
		free(__CTEX_BuildFolder);

	if (__CTEX_LaTeXPreambule != NULL)
		free(__CTEX_LaTeXPreambule);
}

