#include "ctexcpp/error.h"

#include <stddef.h>
#include <string.h>


char __CTEX_errorStack[CTEX_ERROR_STACK_SIZE * CTEX_MAX_ERROR_MESSAGE_SIZE];
char *__CTEX_errorStackTop = __CTEX_errorStack;
size_t __CTEX_pushFailureInRow = 0;



const char *CTEX_GetError() {
	if (!CTEX_HasError())
		return NULL;

	__CTEX_errorStackTop -= CTEX_MAX_ERROR_MESSAGE_SIZE;
	return __CTEX_errorStackTop;
}


CTEX_Bool CTEX_HasError() {
	return __CTEX_errorStackTop == __CTEX_errorStack ? CTEX_FALSE : CTEX_TRUE;
}


CTEX_Result CTEX_PushError(const char *error) {
	if (__CTEX_pushFailureInRow == CTEX_MAX_ERROR_STACK_PUSH_FAILURE_IN_ROW)
		CTEX_ClearError();

	ptrdiff_t byteOffset = __CTEX_errorStackTop - __CTEX_errorStack;
	size_t offset = byteOffset / CTEX_MAX_ERROR_MESSAGE_SIZE;
	if (offset >= CTEX_ERROR_STACK_SIZE) {
		++__CTEX_pushFailureInRow;
		return CTEX_RESULT_FAILURE;
	}

	__CTEX_pushFailureInRow = 0;

	size_t errorStringSize = strlen(error);
	size_t toCopySize = errorStringSize >= CTEX_MAX_ERROR_MESSAGE_SIZE ? CTEX_MAX_ERROR_MESSAGE_SIZE - 1 : errorStringSize;
	memcpy(__CTEX_errorStackTop, error, toCopySize);
	*(__CTEX_errorStackTop + toCopySize) = '\0';

	__CTEX_errorStackTop += CTEX_MAX_ERROR_MESSAGE_SIZE;

	if (errorStringSize != toCopySize)
		return CTEX_RESULT_TOO_BIG_STRING;
	return CTEX_RESULT_SUCCESS;
}


void CTEX_ClearError() {
	__CTEX_errorStackTop = __CTEX_errorStack;
}

