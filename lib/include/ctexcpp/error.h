#pragma once

#include "ctexcpp/bool.h"
#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


#define CTEX_ERROR_STACK_SIZE 16
#define CTEX_MAX_ERROR_MESSAGE_SIZE 256
#define CTEX_MAX_ERROR_STACK_PUSH_FAILURE_IN_ROW 16


const char *CTEX_GetError();
CTEX_Bool CTEX_HasError();
CTEX_Result CTEX_PushError(const char *error);
void CTEX_ClearError();


#ifdef __cplusplus
	}
#endif