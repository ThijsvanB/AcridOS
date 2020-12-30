#include "../include/string.h"

unsigned int strlen(const char* string) {
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return (unsigned int)i;
}

void strcpy(char* dest, const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
}

int strcmp(const char* str1, const char* str2) {
	if (strlen(str1) != strlen(str2)) {
		return 1;
	}
	else {
		int i = 0;
		while (str1[i] != '\0') {
			if (str1[i] != str2[i]) {
				return 1;
			}
			i++;
		}
	}
	return 0;
}