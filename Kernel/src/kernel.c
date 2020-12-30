#include "../include/string.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/serial_port.h"
#include "../include/pit.h"
#include "../include/keyboard.h"

void start() {
	setup_idt();
	init_pic();
	set_pitfreq(1);
	setup_gdt();

	asm("sti");

	cur_enable();

	init_serial();

	clrscr();
	setcolor(0x0F);
	printf("Welcome to AcridOs V0.1.4\n");
}
