#include "ctexcpp/configuration.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ctexcpp/error.h"


char *__CTEX_LaTeXPreambule = NULL;



CTEX_Result CTEX_SetLaTeXPreambule(const char *preambule) {
	if (preambule == NULL) {
		if (__CTEX_LaTeXPreambule != NULL)
			free(__CTEX_LaTeXPreambule);
		__CTEX_LaTeXPreambule = NULL;

		(void)CTEX_PushError("Invalid argument given to `CTEX_SetLaTeXPreambule` : preambule must be non-null");
		return CTEX_RESULT_INVALID_ARGUMENT;
	}

	size_t preambuleLength = strlen(preambule);
	size_t oldPreambuleLength = 0;
	if (__CTEX_LaTeXPreambule != NULL)
		oldPreambuleLength = strlen(__CTEX_LaTeXPreambule);

	if (oldPreambuleLength != preambuleLength) {
		if (__CTEX_LaTeXPreambule != NULL)
			free(__CTEX_LaTeXPreambule);

		__CTEX_LaTeXPreambule = (char*)malloc(sizeof(char) * (preambuleLength + 1));
		if (__CTEX_LaTeXPreambule == NULL) {
			(void)CTEX_PushError("Failed allocation in `CTEX_SetLaTeXPreambule` : can't allocate memory to store the new preambule");
			return CTEX_RESULT_FAILED_ALLOCATION;
		}
	}

	memcpy(__CTEX_LaTeXPreambule, preambule, preambuleLength);
	__CTEX_LaTeXPreambule[preambuleLength] = '\0';
	return CTEX_RESULT_SUCCESS;
}


const char *CTEX_GetLaTeXPreambule() {
	return __CTEX_LaTeXPreambule;
}