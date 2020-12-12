#include "..\include\gdt.h"

struct gdt_desc fillgdtdesc(unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
	struct gdt_desc desc;

	desc.access = access;

	desc.base_low = (base & 0xFFFF);
	desc.base_mid =  (base >> 16) & 0xFF;
	desc.base_high = (base >> 24) & 0xFF;
	
	desc.lim_low = limit & 0xFFFF;
	desc.gran = (limit >> 16) & 0x0F;
	desc.gran |= gran & 0xF0;

	return desc;
}

void setup_gdt() {
	gdt[0] = fillgdtdesc(0x0, 0x0, 0x0, 0x0); //null descriptor
	gdt[1] = fillgdtdesc(0x0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt[2] = fillgdtdesc(0x0, 0xFFFFFFFF, 0x92, 0xCF);

	ptr.base = (unsigned int)&gdt;
	ptr.limit = sizeof(struct gdt_desc) * 3 - 1;

	gdt_flush();
}