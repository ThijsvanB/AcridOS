CC = gcc -ffreestanding

SRCDIR=src

OBJDIR=bin
_OBJ=kernel.o terminal.o string.o math.o ports.o cursor.o gdt.o memory.o idt.o pic.o serial_port.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $<

kernel: $(OBJ)
	nasm -f elf $(SRCDIR)/Kernel_entry.asm -o $(OBJDIR)/Kernel_entry.o
	nasm -f elf $(SRCDIR)/gdtflush.asm -o $(OBJDIR)/gdtflush.o
	nasm -f elf $(SRCDIR)/idtload.asm -o $(OBJDIR)/idtload.o
	
	ld -T NUL -o $(OBJDIR)/kernel.tmp -Ttext 0x1000 $(OBJDIR)/Kernel_entry.o $(OBJDIR)/gdtflush.o $(OBJDIR)/idtload.o $^
	objcopy -O binary $(OBJDIR)/kernel.tmp $(OBJDIR)/kernel.bin
