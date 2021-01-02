#include "../include/shell.h"

void ProcKey(unsigned char key) {
	unsigned short* vidmem;
	switch (key) {
	case '\n':
		//Get the command
		vidmem = (unsigned short*)SCREENADDRESS;
		putc('\n');
		int row = getrow() - 1, i = 0;
		char cmd[80];
		char col = getcol();
		while((i < 79) && (vidmem[row * 80 + i] != ((unsigned short)col << 8))) {
			cmd[i] = vidmem[row * 80 + i];
			i++;
		}
		if (strcmp(cmd, "test") == 0) {
			printf("Hello\n");
		}
		else {
			printf("Command unknown\n");
		}
		break;
	default:
		putc(key);
		break;
	}
}