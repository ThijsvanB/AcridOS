#include "..\include\PCI.h"
#include "..\include\ports.h"

unsigned int pciConfigReadReg(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset) {
	unsigned int lbus = (unsigned int)bus;
	unsigned int lslot = (unsigned int)slot;
	unsigned int lfunc = (unsigned int)func;

	unsigned int addr = (lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xFC) | 0x80000000;

	outl(0xCF8, addr);

	return inl(0xCFC);
}

void checkDevices() {
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 32; j++) {
			unsigned int VenDev = pciConfigReadReg(i, j, 0, 0);
			if ((VenDev & (unsigned int)0x0000FFFF) != 0xFFFF) {
				pci_header device = getDevice(i, j);
			}
		}
	}
	printf("Done devices");
}

pci_header getDevice(unsigned char bus, unsigned char slot) {
	pci_header result;

	unsigned int reg = pciConfigReadReg(bus, slot, 0, 0);
	result.vendor = (reg & (unsigned int)0x0000FFFF) >> 0;
	result.device = (reg & (unsigned int)0xFFFF0000) >> 16;
	
	reg = pciConfigReadReg(bus, slot, 0, 4);
	result.status = (reg & (unsigned int)0x0000FFFF) >> 0;
	result.command = (reg & (unsigned int)0xFFFF0000) >> 16;

	reg = pciConfigReadReg(bus, slot, 0, 8);
	result.revision = (reg & (unsigned int)0x000000FF) >> 0;
	result.progIf = (reg & (unsigned int)0x0000FF00) >> 8;
	result.subclass = (reg & (unsigned int)0x00FF0000) >> 16;
	result.class_code = (reg & (unsigned int)0xFF000000) >> 24;

	reg = pciConfigReadReg(bus, slot, 0, 12);
	result.cacheLineSize = (reg & (unsigned int)0x000000FF) >> 0;
	result.latency = (reg & (unsigned int)0x0000FF00) >> 8;
	result.header_type = (reg & (unsigned int)0x00FF0000) >> 16;
	result.BIST = (reg & (unsigned int)0xFF000000) >> 24;

	sp_printf("Vendor: %i, Device: %i\n", result.vendor, result.device);
	sp_printf("%i %i\n", result.status, result.command);
	sp_printf("%i %i %i %i\n", result.revision, result.progIf, result.subclass, result.class_code);
	sp_printf("%i %i %i %i\n\n", result.cacheLineSize, result.latency, result.header_type, result.BIST);

	return result;
}