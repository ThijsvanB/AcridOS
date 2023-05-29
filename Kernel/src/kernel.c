#include "../include/string.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/pit.h"
#include "../include/keyboard.h"
#include "../include/vga.h"
#include "../include/USB.h"
#include "../include/PCI.h"

/*Main method which is called after booting and switching to 32 bit*/
void start() {
	setup_idt();
	init_pic();
	set_pitfreq(1);
	setup_gdt();

	asm("sti");

	init_serial();
	terminalInit();

	clrscr();
	setcolor(0xF);
	printf("Welcome to AcridOs V0.2.0\n");

	findUSBDevices();
	checkPCIDevices();
}
