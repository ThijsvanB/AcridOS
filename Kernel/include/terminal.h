#define SCREENADDRESS 0xB8000

#include "math.h"
#include "string.h"
#include "cursor.h"

#ifdef __TERMINAL__

char col = 0;
char row = 0;
char color = 0x0F;

#endif

void clrscr();

void setcolor(char c);

void putc(char c);

void puti(int i);

void puts(char* s);

void printf(char* format, ...);