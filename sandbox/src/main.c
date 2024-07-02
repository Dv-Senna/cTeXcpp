#include <stdio.h>
#include <stdlib.h>

#include <ctexcpp/ctexcpp.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define POOL_ALL_ERRORS while(CTEX_HasError()) printf("ERROR : %s\n", CTEX_GetError())


int main() {
	if (CTEX_Init() != CTEX_RESULT_SUCCESS)
		POOL_ALL_ERRORS;

	printf("LaTeX Preambule : %s\n", CTEX_GetLaTeXPreambule());

	CTEX_Hash hash = CTEX_HashString("Hello World!");
	printf("HASH : %d\n", hash);

	const char *base64 = CTEX_EncodeNumberToBase64(hash);
	printf("BASE64 : %s\n", base64);
	free((char*)base64);


	CTEX_ParseLaTeX("E = \\gamma m_0 c^2", 10, CTEX_TRUE);


	CTEX_Quit();

	return 0;
}