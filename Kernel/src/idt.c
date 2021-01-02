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
	idt[1] = fillidtdesc((unsigned long)irq1_handler, 0x08, 0x8E00);
	idt[2] = fillidtdesc((unsigned long)irq2_handler, 0x08, 0x8E00);
	idt[3] = fillidtdesc((unsigned long)irq3_handler, 0x08, 0x8E00);
	idt[4] = fillidtdesc((unsigned long)irq4_handler, 0x08, 0x8E00);
	idt[5] = fillidtdesc((unsigned long)irq5_handler, 0x08, 0x8E00);
	idt[6] = fillidtdesc((unsigned long)irq6_handler, 0x08, 0x8E00);
	idt[7] = fillidtdesc((unsigned long)irq7_handler, 0x08, 0x8E00);
	idt[8] = fillidtdesc((unsigned long)irq8_handler, 0x08, 0x8E00);
	idt[9] = fillidtdesc((unsigned long)irq9_handler, 0x08, 0x8E00);
	idt[10] = fillidtdesc((unsigned long)irq10_handler, 0x08, 0x8E00);
	idt[11] = fillidtdesc((unsigned long)irq11_handler, 0x08, 0x8E00);
	idt[12] = fillidtdesc((unsigned long)irq12_handler, 0x08, 0x8E00);
	idt[13] = fillidtdesc((unsigned long)irq13_handler, 0x08, 0x8E00);
	idt[14] = fillidtdesc((unsigned long)irq14_handler, 0x08, 0x8E00);
	idt[15] = fillidtdesc((unsigned long)irq15_handler, 0x08, 0x8E00);
	idt[16] = fillidtdesc((unsigned long)irq16_handler, 0x08, 0x8E00);
	idt[17] = fillidtdesc((unsigned long)irq17_handler, 0x08, 0x8E00);
	idt[18] = fillidtdesc((unsigned long)irq18_handler, 0x08, 0x8E00);
	idt[19] = fillidtdesc((unsigned long)irq19_handler, 0x08, 0x8E00);
	idt[20] = fillidtdesc((unsigned long)irq20_handler, 0x08, 0x8E00);
	idt[30] = fillidtdesc((unsigned long)irq30_handler, 0x08, 0x8E00);
	idt[31] = fillidtdesc((unsigned long)irq31_handler, 0x08, 0x8E00);
	idt[32] = fillidtdesc((unsigned long)irq32_handler, 0x08, 0x8E00);
	idt[33] = fillidtdesc((unsigned long)irq33_handler, 0x08, 0x8E00);

	idtptr.base = &idt;
	idtptr.limit = (sizeof(idt)) - 1;

	idt_load();
}