OBJ=Acrid

all: $(OBJ)
	
Acrid: ACR_Boot kern
	type Boot\ACR_Boot.bin Kernel\bin\kernel.bin > Acrid.iso
	qemu-system-i386 Acrid.iso -d int -serial stdio
	
ACR_Boot:
	make -C Boot
	
kern: 
	make -C Kernel