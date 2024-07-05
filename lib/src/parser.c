#include "ctexcpp/parser.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CTEX_WINDOWS
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif

#include <stb_image.h>

#include "ctexcpp/configuration.h"
#include "ctexcpp/error.h"
#include "ctexcpp/numberEncoder.h"
#include "ctexcpp/hash.h"


CTEX_Result makedir(const char *directory) {
#ifdef CTEX_WINDOWS
	if (_mkdir(directory) != 0 && errno != EEXIST) {
		CTEX_PushError("Can't create folder on windows");
		return CTEX_RESULT_FAILURE;
	}
#else
	if (mkdir(directory, S_IRWXU) != 0 && errno != EEXIST) {
		CTEX_PushError("Can't create folder on unix");
		return CTEX_RESULT_FAILURE;
	}
#endif

	return CTEX_RESULT_SUCCESS;
}


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
	CTEX_Image result;

	String latexFileContent;
	String pdflatexCommand;
	String imageMagickCommand;
	String latexFilePath;
	String pdfFilePath;
	String pngFilePath;

	size_t fileNameLength = strlen(fileName);
	size_t latexLength = strlen(latex);
	size_t preambuleLength = strlen(CTEX_GetLaTeXPreambule());
	size_t buildFolderLength = strlen(CTEX_GetBuildFolder());

	float fontSizeInPT = fontSize * 72.27f / 300.f;

	latexFileContent.size = 272 + latexLength + preambuleLength;
	latexFileContent.str = malloc(latexFileContent.size + 1);
	snprintf(latexFileContent.str, latexFileContent.size + 1, "\
\\documentclass[preview, border=1pt]{standalone}\n\
\\usepackage{mathrsfs}\n\
\\usepackage{slashed}\n\
\\usepackage{amsmath}\n\
\\usepackage{amssymb}\n\
\\usepackage{xcolor}\n\
\\usepackage{fix-cm}\n\
%s\n\
\\begin{document}\n\
{\\fontsize{%.4fpt}{%.4fpt}\\selectfont\n\
\\color{white}\n\
$%s$\n\
}\n\
\\end{document}", CTEX_GetLaTeXPreambule(), fontSizeInPT, fontSizeInPT, latex);

	latexFilePath.size = buildFolderLength + fileNameLength + 5;
	latexFilePath.str = malloc(latexFilePath.size + 1);
	snprintf(latexFilePath.str, latexFilePath.size + 1, "%s/%s.tex", CTEX_GetBuildFolder(), fileName);

	pdfFilePath.size = buildFolderLength + fileNameLength + 5;
	pdfFilePath.str = malloc(pdfFilePath.size + 1);
	snprintf(pdfFilePath.str, pdfFilePath.size + 1, "%s/%s.pdf", CTEX_GetBuildFolder(), fileName);

	pngFilePath.size = buildFolderLength + fileNameLength + 5;
	pngFilePath.str = malloc(pngFilePath.size + 1);
	snprintf(pngFilePath.str, pngFilePath.size + 1, "%s/%s.png", CTEX_GetBuildFolder(), fileName);

	pdflatexCommand.size = buildFolderLength * 2 + latexFilePath.size + 44;
	pdflatexCommand.str = malloc(pdflatexCommand.size + 1);
	snprintf(pdflatexCommand.str, pdflatexCommand.size + 1,
		"pdflatex -aux-directory=%s -output-directory=%s %s",
		CTEX_GetBuildFolder(), CTEX_GetBuildFolder(), latexFilePath.str
	);

	imageMagickCommand.size = pdfFilePath.size + pngFilePath.size + 43;
	imageMagickCommand.str = malloc(imageMagickCommand.size + 1);
	snprintf(imageMagickCommand.str, imageMagickCommand.size + 1,
		"magick -density 300 -depth 8 -quality 100 %s %s",
		pdfFilePath.str, pngFilePath.str
	);


	if (makedir(CTEX_GetBuildFolder()) != CTEX_RESULT_SUCCESS) {
		CTEX_PushError("Can't create latex build folder");
		goto parse_error;
	}

	FILE *latexFile = fopen(latexFilePath.str, "w");
	if (latexFile == NULL) {
		CTEX_PushError("Can't open / create latex file");
		goto parse_error;
	}

	fprintf(latexFile, latexFileContent.str);

	fclose(latexFile);

	if (system(pdflatexCommand.str) != 0) {
		CTEX_PushError("Failed to compile LaTeX");
		goto parse_error;
	}

	if (system(imageMagickCommand.str) != 0) {
		CTEX_PushError("Failed to convert pdf to png");
		goto parse_error;
	}


	result.pixels = stbi_load(pngFilePath.str, &result.width, &result.height, &result.channels, 4);
	if (result.pixels == NULL) {
		CTEX_PushError("Can't load image file");
		goto parse_error;
	}


	goto parse_end;

parse_error:
	result.pixels = NULL;
	result.width = -1;
	result.height = -1;
	result.channels = -1;

parse_end:
	free(imageMagickCommand.str);
	free(pdflatexCommand.str);
	free(pngFilePath.str);
	free(pdfFilePath.str);
	free(latexFilePath.str);
	free(latexFileContent.str);

	return result;
}

