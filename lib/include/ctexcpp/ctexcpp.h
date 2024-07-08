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


/**
 * @brief Initialize ctexcpp
 * @return `CTEX_RESULT_SUCCESS` if succeed, an error code otherwise
 */
CTEX_Result CTEX_Init();
/**
 * @brief Quit ctexcpp. All ressources you allocated must have been freed prior to calling this function
 */
void CTEX_Quit();


#ifdef __cplusplus
	}
#endif