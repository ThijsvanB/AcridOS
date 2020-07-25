OBJ=Acrid

all: $(OBJ)
	
Acrid: ACR_Boot kern
	type Boot\ACR_Boot.bin Kernel\bin\kernel.bin > Acrid.img
	qemu-system-i386 Acrid.img
	
ACR_Boot:
	make -C Boot
	
kern: 
	make -C Kernel