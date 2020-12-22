#include "../include/terminal.h"
#include "../include/string.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/serial_port.h"

void start() {
	cur_enable();

	init_serial();

	setup_gdt();
	setup_idt();

	clrscr();
	setcolor(0x0F);
	printf("Welcome to AcridOs V0.1.2\n");

	cur_disable();
}
