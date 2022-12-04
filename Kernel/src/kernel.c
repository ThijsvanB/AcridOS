#include "../include/string.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/pit.h"
#include "../include/keyboard.h"
#include "../include/vga.h"

/*Main method which is called after booting and switching to 32 bit*/
void start() {
	setup_idt();
	init_pic();
	set_pitfreq(1);
	setup_gdt();

	asm("sti");

	cur_enable();

	init_serial();

	clrscr();
	setcolor(0xF);
	printf("Welcome to AcridOs V0.2.0\n");
}
