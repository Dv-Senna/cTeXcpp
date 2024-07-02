#pragma once

#include "ctexcpp/bool.h"


#ifdef __cplusplus
	extern "C" {
#endif


typedef struct {
	void *pixels;
	int width;
	int height;
	int channels;
} CTEX_Image;

CTEX_Image CTEX_ParseLaTeX(const char *latex, int fontSize, CTEX_Bool useCache);


#ifdef __cplusplus
	}
#endif