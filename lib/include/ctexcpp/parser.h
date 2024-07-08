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


/**
 * @brief Parse the given LateX
 * @param latex The formula you want to parse
 * @param fontSize The size of the font, in pixels
 * @param useCache `CTEX_TRUE` to use caching, `CTEX_FALSE` otherwise. It is recommended to use caching except if your formula is a one-time use
 * @return The image generated from the formula
 */
CTEX_Image CTEX_ParseLaTeX(const char *latex, int fontSize, CTEX_Bool useCache);


#ifdef __cplusplus
	}
#endif