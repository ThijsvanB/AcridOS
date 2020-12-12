#include "../include/terminal.h"
#include "../include/string.h"
#include "../include/ports.h"
#include "../include/gdt.h"
#include "../include/idt.h"

void start() {
	cur_enable();

	setup_gdt();
	setup_idt();

	clrscr();
	setcolor(0x0F);
	printf("Welcome to AcridOs V0.1.2\n");

	cur_disable();
}
