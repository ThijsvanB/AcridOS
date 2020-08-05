#include "..\include\memory.h"

struct gdt_desc {
	unsigned short lim_low;
	unsigned short base_low;
	unsigned char base_mid;
	unsigned char access;
	unsigned char gran;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct gdt_desc gdt[3];
struct gdt_ptr ptr;

struct gdt_desc filldesc(unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void setup_gdt();

extern void gdt_flush();