#include "..\include\idt.h"

struct idt_desc fillidtdesc(unsigned long off, unsigned short sel, unsigned short type_attr) {
	struct idt_desc desc;

	desc.off_low = off & 0xffff;
	desc.off_high = (off >> 16) & 0xFFFF;
	desc.type = type_attr;
	desc.sel = sel;

	return desc;
}

void setup_idt() {
	for (int i = 0; i < 256; i++) {
		idt[i] = fillidtdesc((unsigned long)irqdef_handler, 0x08, 0x8E00);
	}

	idt[0] = fillidtdesc((unsigned long)irq0_handler, 0x08, 0x8E00);
	idt[13] = fillidtdesc((unsigned long)irq13_handler, 0x08, 0x8E00);
	idt[32] = fillidtdesc((unsigned long)irq32_handler, 0x08, 0x8E00);
	idt[33] = fillidtdesc((unsigned long)irq33_handler, 0x08, 0x8E00);

	idtptr.base = &idt;
	idtptr.limit = (sizeof(idt)) - 1;

	idt_load();
}