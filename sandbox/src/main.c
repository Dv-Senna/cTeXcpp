#include <stdio.h>

#include <ctexcpp/ctexcpp.h>

#define POOL_ALL_ERRORS while(CTEX_HasError()) printf("ERROR : %s\n", CTEX_GetError())


int main() {
	if (CTEX_Init() != CTEX_RESULT_SUCCESS)
		POOL_ALL_ERRORS;

	printf("LaTeX Preambule : %s\n", CTEX_GetLaTeXPreambule());

	CTEX_Quit();

	return 0;
}