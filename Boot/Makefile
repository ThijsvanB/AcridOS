OBJ=ACR_Boot

all: $(OBJ)

ACR_Boot: ACR_Boot.asm
	nasm -f bin -o $@.bin $^
	
clean:
	rm -f $(OBJ) *.o