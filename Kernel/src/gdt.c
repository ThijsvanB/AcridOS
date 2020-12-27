#include "..\include\gdt.h"

struct gdt_desc fillgdtdesc(unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
	struct gdt_desc desc;

	if (limit > 0x10000) {
		limit = limit >> 12;
		desc.gran = 0xC0;
	}
	else {
		desc.gran = 0x40;
	}

	desc.access = access;

	desc.base_low = (base & 0xFFFF);
	desc.base_mid =  (base >> 16) & 0xFF;
	desc.base_high = (base >> 24) & 0xFF;
	
	desc.lim_low = limit & 0xFFFF;
	desc.gran |= (limit >> 16) & 0x0F;

	return desc;
}

void setup_gdt() {
	struct tss deftss;
	deftss.debuf_flag = 0x0;
	deftss.io_flag = 0x0;
	deftss.ESP0 = 0x20000;
	deftss.SS0 = 0x18;

	gdt[0] = fillgdtdesc(0x0, 0x0, 0x0, 0x0); //null descriptor
	gdt[1] = fillgdtdesc(0x0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt[2] = fillgdtdesc(0x0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt[3] = fillgdtdesc(&deftss, sizeof(deftss), 0x89, 0xCF);

	set_gdt((unsigned int)&gdt, sizeof(gdt));

	gdt_flush();
}