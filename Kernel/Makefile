CC = gcc -ffreestanding -Wall

SRCDIR=src

OBJDIR=bin
_OBJ=kernel.o terminal.o string.o math.o ports.o gdt.o memory.o idt.o pic.o serial_port.o keyboard.o pit.o exceptions.o vga.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $<

kernel: $(OBJ)
	nasm -f elf $(SRCDIR)/Kernel_entry.asm -o $(OBJDIR)/Kernel_entry.o
	nasm -f elf $(SRCDIR)/gdtflush.asm -o $(OBJDIR)/gdtflush.o
	nasm -f elf $(SRCDIR)/idtload.asm -o $(OBJDIR)/idtload.o
	
	ld -T nul -Ttext 0x1000 $(OBJDIR)/Kernel_entry.o $(OBJDIR)/gdtflush.o $(OBJDIR)/idtload.o $^ -o $(OBJDIR)/kernel.tmp
	objcopy -O binary $(OBJDIR)/kernel.tmp $(OBJDIR)/kernel.bin
