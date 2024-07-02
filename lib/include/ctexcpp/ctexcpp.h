#pragma once

#include "ctexcpp/bool.h"
#include "ctexcpp/configuration.h"
#include "ctexcpp/error.h"
#include "ctexcpp/hash.h"
#include "ctexcpp/numberEncoder.h"
#include "ctexcpp/parser.h"
#include "ctexcpp/result.h"


#ifdef __cplusplus
	extern "C" {
#endif


CTEX_Result CTEX_Init();
void CTEX_Quit();


#ifdef __cplusplus
	}
#endif