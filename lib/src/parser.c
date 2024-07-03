#include "ctexcpp/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stb_image.h>

#include "ctexcpp/configuration.h"
#include "ctexcpp/error.h"
#include "ctexcpp/numberEncoder.h"
#include "ctexcpp/hash.h"


CTEX_Image parseWithHash(const char *latex, int fontSize);
CTEX_Image parseWithoutHash(const char *latex, int fontSize, const char *fileName);


CTEX_Image CTEX_ParseLaTeX(const char *latex, int fontSize, CTEX_Bool useCache) {
	if (useCache)
		return parseWithHash(latex, fontSize);
	return parseWithoutHash(latex, fontSize, "UNCACHED_LATEX_FILE");
}


CTEX_Image parseWithHash(const char *latex, int fontSize) {
	CTEX_Hash hash = CTEX_HashString(latex);
	const char *hashString = CTEX_EncodeNumberToBase64(hash);
	size_t hashLength = strlen(hashString);
	size_t folderLength = strlen(CTEX_GetBuildFolder());

	size_t filePathLength = folderLength + hashLength + 5; // +5 for '/' and '.png'
	char *filePath = malloc(sizeof(char) * (filePathLength + 1));
	(void)snprintf(filePath, filePathLength + 1, "%s/%s.png", CTEX_GetBuildFolder(), hashString);

	CTEX_Image result;
	FILE *pngFiles = fopen(filePath, "r");
	if (pngFiles == NULL)
		result = parseWithoutHash(latex, fontSize, hashString);
	else {
		fclose(pngFiles);
		result.pixels = stbi_load(filePath, &result.width, &result.height, &result.channels, 4);
	}

	free(filePath);
	free((char*)hashString);

	return result;
}


typedef struct {
	char *str;
	size_t size;
} String;


CTEX_Image parseWithoutHash(const char *latex, int fontSize, const char *fileName) {
	String latexFileContent;
	String pdflatexCommand;
	String imageMagickCommand;
	String latexFilePath;
	String pngFilePath;

	size_t fileNameLength = strlen(fileName);
	size_t latexLength = strlen(latex);
	size_t preambuleLength = strlen(CTEX_GetLaTeXPreambule());

	float fontSizeInPT = fontSize * 72.27f / 300.f;

	latexFileContent.size = 130 + latexLength + preambuleLength;
	latexFileContent.str = malloc(latexFileContent.size + 1);
	snprintf(latexFileContent.str, latexFileContent.size + 1, "\
\\documentclass[preview]{standalone}\n\
%s\n\
\\begin{document}\n\
{\\fontsize{%.4fpt}{%.4fpt}\\selectfont\n\
$%s$\n\
}\n\
\\end{document}", CTEX_GetLaTeXPreambule(), fontSizeInPT, fontSizeInPT, latex);

	printf(latexFileContent.str);

	pdflatexCommand.str = malloc(pdflatexCommand.size + 1);
	//snprintf(pdflatexCommand.str, pdflatexCommand.size + 1, "");

	imageMagickCommand.str = malloc(imageMagickCommand.size + 1);
	//snprintf(imageMagickCommand.str, imageMagickCommand.size + 1, "");

	latexFilePath.str = malloc(latexFilePath.size + 1);
	//snprintf(latexFilePath.str, latexFilePath.size + 1, "%s/%s.tex", CTEX_GetBuildFolder(), fileName);

	pngFilePath.str = malloc(pngFilePath.size + 1);
	//snprintf(pngFilePath.str, pngFilePath.size + 1, "%s/%s.png", CTEX_GetBuildFolder(), fileName);

	free(pngFilePath.str);
	free(latexFilePath.str);
	free(imageMagickCommand.str);
	free(pdflatexCommand.str);
	free(latexFileContent.str);
}

