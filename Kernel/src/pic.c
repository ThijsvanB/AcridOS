#include "..\include\pic.h"
#include "..\include\ports.h"

#define PIC1COM 0x20
#define PIC1DAT 0x21
#define PIC2COM 0xA0
#define PIC2DAT 0xA1

void init_pic() {
	unsigned char x = inb(PIC1DAT), y = inb(PIC2DAT);

	outb(PIC1COM, 0x11);
	outb(PIC2COM, 0x11);

	outb(PIC1DAT, 0x20);
	outb(PIC2DAT, 0x70);

	outb(PIC1DAT, 0x04);
	outb(PIC2DAT, 0x02);

	outb(PIC1DAT, 0x01);
	outb(PIC2DAT, 0x01);

	outb(PIC1DAT, 0x0);
	outb(PIC2DAT, 0x0);

	outb(PIC1DAT, x);
	outb(PIC2DAT, y);
}

void pic_eoi(unsigned char irq) {
	if (irq > 7) {
		outb(PIC2COM, 0x20);
	}
	outb(PIC1COM, 0x20);
}