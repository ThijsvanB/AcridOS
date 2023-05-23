#define KC_BACK 0x08

#define COLMAX 40
#define ROWMAX 25

#include "math.h"
#include "serial_port.h"
#include "memory.h"
#include "vga.h"

void terminalInit();

void setcolor(char c);

void putc(char c);
void puti(int i);
void puts(char* s);

void printf(char* format, ...);

int getrow();
int getcol();