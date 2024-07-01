#include "ctexcpp/hash.h"

#include <stddef.h>


CTEX_Hash CTEX_HashString(const char *str) {
	if (str == NULL)
		return 0;

	CTEX_Hash hash = 0;
	for (const char *chr = str; *chr != '\0'; ++chr)
		hash += *chr * (1 + chr - str);
	return hash;
}

