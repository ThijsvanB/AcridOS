#include "..\include\memory.h"

void memset(void* dest, unsigned char value, int size) {
	char* ptr = dest;
	for (int i = 0; i < size; i++) {
		ptr[i] = value;
	}
}

void memcpy(void* dest, void* src, int size) {
	char* ptr = dest;
	char* ptr2 = src;
	for (int i = 0; i < size; i++) {
		ptr[i] = ptr2[i];
	}
}