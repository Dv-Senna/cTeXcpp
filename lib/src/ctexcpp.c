#include "ctexcpp/ctexcpp.h"

#include "ctexcpp/configuration.h"
#include "ctexcpp/error.h"



CTEX_Result CTEX_Init() {
	if (CTEX_SetLaTeXPreambule(" ") != CTEX_RESULT_SUCCESS) {
		CTEX_PushError("Failure in `CTEX_Init` : Can't set LaTeX preambule");
		return CTEX_RESULT_FAILURE;
	}

	if (CTEX_SetBuildFolder("latex") != CTEX_RESULT_SUCCESS) {
		CTEX_PushError("Failure in `CTEX_Init` : Can't set build folder");
		return CTEX_RESULT_FAILURE;
	}

	return CTEX_RESULT_SUCCESS;
}


void CTEX_Quit() {
	CTEX_FreeConfiguration();
}


