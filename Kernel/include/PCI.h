#include "..\include\terminal.h"

typedef struct PCI_HEADER {
	unsigned short vendor;
	unsigned short device;
	unsigned short status;
	unsigned short command;
	unsigned char class_code;
	unsigned char subclass;
	unsigned char progIf;
	unsigned char revision;
	unsigned char BIST;
	unsigned char header_type;
	unsigned char latency;
	unsigned char cacheLineSize;
} pci_header;

unsigned int pciConfigReadReg(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset);

void checkDevices();

pci_header getDevice(unsigned char bus, unsigned char slot);