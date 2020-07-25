CC = gcc -ffreestanding

SRCDIR=src

OBJDIR=bin
_OBJ=kernel.o terminal.o string.o math.o ports.o cursor.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $<

kernel: $(OBJ)
	nasm -f elf $(SRCDIR)/Kernel_entry.asm -o $(OBJDIR)/Kernel_entry.o
	ld -T NUL -o $(OBJDIR)/kernel.tmp -Ttext 0x1000 $(OBJDIR)/Kernel_entry.o $^
	objcopy -O binary $(OBJDIR)/kernel.tmp $(OBJDIR)/kernel.bin