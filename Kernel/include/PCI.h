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

typedef struct PCI_HEADER0 {
	pci_header header;
	unsigned int baseAddrs[6];
	unsigned int cardbus;
	unsigned short subsystemId;
	unsigned short subsytemVendorId;
	unsigned int expansionRom;
	unsigned char capabilitiesPointer;
	unsigned char maxLatency;
	unsigned char minGrant;
	unsigned char interruptPin;
	unsigned char interruptLine;
} pci_header0;

typedef struct PCI_DEVICE {
	pci_header header;

	pci_header0 header0;
} pci_device;

unsigned int pciConfigReadReg(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset);

void checkPCIDevices();

pci_device getPCIDevice(unsigned char bus, unsigned char slot);

pci_header0 getPCI0Header(unsigned char bus, unsigned char slot);