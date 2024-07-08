#pragma once

#include "ctexcpp/bool.h"
#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


#define CTEX_ERROR_STACK_SIZE 16
#define CTEX_MAX_ERROR_MESSAGE_SIZE 256
#define CTEX_MAX_ERROR_STACK_PUSH_FAILURE_IN_ROW 16


/**
 * @brief Get the last error pushed on the error stack. Consider looping with `CTEX_HasError()` to empty the error stack correctly
 */
const char *CTEX_GetError();
/**
 * @brief Return `CTEX_TRUE` if the error stack is not empty, `CTEX_FALSE` otherwise
 */
CTEX_Bool CTEX_HasError();
/**
 * @brief Push an error on the error stack
 * @return `CTEX_RESULT_SUCCESS` if succeed, an error code otherwise
 * @warning Unless you have a really good reason not to do so, you want to ignore the return code
 */
CTEX_Result CTEX_PushError(const char *error);
/**
 * @brief Clear the error stack
 */
void CTEX_ClearError();


#ifdef __cplusplus
	}
#endif