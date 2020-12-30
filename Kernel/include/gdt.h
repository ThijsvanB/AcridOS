#include "memory.h"
#include "serial_port.h"

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

struct tss {
	unsigned short prev_task, prev_task_res;

	unsigned int ESP0;
	unsigned short SS0, SS0res;
	unsigned int ESP1;
	unsigned short SS1, SS1res;
	unsigned int ESP2;
	unsigned short SS2, SS2res;

	unsigned int CR3, EIP, EFLAGS, EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI;
	unsigned short ES, ESres, CS, CSres, SS, SSres, DS, DSres, FS, FSres, GS, GSres;

	unsigned short ldt_sel, ldt_sel_res;
	unsigned short debuf_flag, io_flag;

} __attribute__((packed));

struct gdt_desc gdt[8];

struct gdt_desc fillgdtdesc(unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void setup_gdt();

extern void set_gdt(unsigned short limit, unsigned int base);
extern void gdt_flush();