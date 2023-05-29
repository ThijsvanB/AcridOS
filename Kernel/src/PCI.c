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

void checkPCIDevices() {
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 32; j++) {
			unsigned int VenDev = pciConfigReadReg(i, j, 0, 0);
			if ((VenDev & (unsigned int)0x0000FFFF) != 0xFFFF) {
				pci_device device = getPCIDevice(i, j);
				sp_printf("\n");
			}
		}
	}
	printf("Done devices");
}

pci_device getPCIDevice(unsigned char bus, unsigned char slot) {
	pci_device result;

	unsigned int reg = pciConfigReadReg(bus, slot, 0, 0);
	result.header.vendor = (reg & (unsigned int)0x0000FFFF) >> 0;
	result.header.device = (reg & (unsigned int)0xFFFF0000) >> 16;
	
	reg = pciConfigReadReg(bus, slot, 0, 4);
	result.header.status = (reg & (unsigned int)0x0000FFFF) >> 0;
	result.header.command = (reg & (unsigned int)0xFFFF0000) >> 16;

	reg = pciConfigReadReg(bus, slot, 0, 8);
	result.header.revision = (reg & (unsigned int)0x000000FF) >> 0;
	result.header.progIf = (reg & (unsigned int)0x0000FF00) >> 8;
	result.header.subclass = (reg & (unsigned int)0x00FF0000) >> 16;
	result.header.class_code = (reg & (unsigned int)0xFF000000) >> 24;

	reg = pciConfigReadReg(bus, slot, 0, 0xC);
	result.header.cacheLineSize = (reg & (unsigned int)0x000000FF) >> 0;
	result.header.latency = (reg & (unsigned int)0x0000FF00) >> 8;
	result.header.header_type = (reg & (unsigned int)0x00FF0000) >> 16;
	result.header.BIST = (reg & (unsigned int)0xFF000000) >> 24;

	switch (result.header.header_type) {
	case 0:
		sp_printf("Detected PCI header 0\n");
		result.header0 = getPCI0Header(bus, slot);
		break;
	case 1:
		sp_printf("Detected PCI header 1\n");
		break;
	case 2:
		sp_printf("Detected PCI header 2\n");
		break;
	default:
		sp_printf("Error detecting PCI header, value gotten: %i\n", result.header.header_type);
		break;
	}

	sp_printf("Vendor: %i, Device: %i\n", result.header.vendor, result.header.device);
	sp_printf("%i %i\n", result.header.status, result.header.command);
	sp_printf("%i %i %i %i\n", result.header.revision, result.header.progIf, result.header.subclass, result.header.class_code);
	sp_printf("%i %i %i %i\n", result.header.cacheLineSize, result.header.latency, result.header.header_type, result.header.BIST);

	sp_printf("Header %i:\n", result.header.header_type);
	switch (result.header.header_type) {
	case 0:
		for (int i = 0; i < 6; i++) {
			sp_printf("%i\n", result.header0.baseAddrs[i]);
		}
		sp_printf("%i\n", result.header0.cardbus);
		sp_printf("%i %i\n", result.header0.subsystemId, result.header0.subsytemVendorId);
		sp_printf("%i\n", result.header0.expansionRom);
		sp_printf("%i\n", result.header0.capabilitiesPointer);
		sp_printf("%i %i %i %i\n", result.header0.maxLatency, result.header0.minGrant, result.header0.interruptPin, result.header0.interruptLine);
		break;
	default:
		sp_printf("No specific header\n");
		break;
	}

	return result;
}

pci_header0 getPCI0Header(unsigned char bus, unsigned char slot) {
	pci_header0 result;

	for (int i = 0; i < 6; i++) {
		result.baseAddrs[i] = pciConfigReadReg(bus, slot, 0, 0x10 + i * 4);
	}
	result.cardbus = pciConfigReadReg(bus, slot, 0, 0x28);

	unsigned int reg = pciConfigReadReg(bus, slot, 0, 0x2C);
	result.subsystemId = (reg & 0xFFFF0000) >> 16;
	result.subsytemVendorId = (reg & 0x0000FFFF) >> 0;

	result.expansionRom = pciConfigReadReg(bus, slot, 0, 0x30);

	result.capabilitiesPointer = (pciConfigReadReg(bus, slot, 0, 0x34) & 0x000000FF) >> 0;

	reg = pciConfigReadReg(bus, slot, 0, 0x2C);
	result.maxLatency = (reg & 0xFF000000) >> 24;
	result.minGrant = (reg & 0x00FF0000) >> 16;
	result.interruptPin = (reg & 0x0000FF00) >> 8;
	result.interruptLine = (reg & 0x000000FF) >> 0;

	return result;
}