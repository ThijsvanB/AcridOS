#include "ports.h"
#include "math.h"
#include "string.h"

#define PORT 0x3f8

void init_serial();

int serial_recieved();
unsigned char read_serial();

int is_transmit_empty();
void write_serial(char a);

void sp_putc(char a);
void sp_puti(int i);
void sp_puts(char* s);
void sp_printf(char* format, ...);