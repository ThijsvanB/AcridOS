#include "ports.h"
#include "terminal.h"
#include "memory.h"
#include "pic.h"
#include "serial_port.h"

struct idt_desc {
	unsigned short off_low;
	unsigned short sel;
	unsigned short type;
	unsigned short off_high;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_desc idt[255];
struct idt_ptr idtptr;

struct idt_desc fillidtdesc(unsigned long off, unsigned short sel, unsigned short type_attr);

void setup_idt();

extern void idt_load();
extern void irqdef_handler();
extern void irq0_handler(void);
extern void irq13_handler(void);
extern void irq32_handler(void);
extern void irq33_handler(void);