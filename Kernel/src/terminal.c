#define __TERMINAL__
#include "../include/terminal.h"

void clrscr() {
	unsigned short* vidmem = (unsigned short*)0xB8000;

	for (int i = 0; i < 2000; i++) {
		vidmem[i] = ((unsigned short)color << 8) | ' ';
	}
	col = 0;
	row = 0;

	cur_setpos(0, 0);
}

void setcolor(char c) {
	color = c;
}

void putc(char c) {
	unsigned short* vidmem = (unsigned short*)0xB8000;
	unsigned short index = row * 80 + col;

	switch (c) {
	case '\n':
		col = 0;
		row++;
		break;
	case KC_BACK:
		if (col > 0) {
			col--;
			vidmem[index - 1] = ((unsigned short)color << 8) | ' ';
		}
		break;
	default:
		vidmem[index] = ((unsigned short)color << 8) | c;
		col++;
		break;
	}

	if (col == 80) {
		col = 0;
		row++;
	}

	cur_setpos(col, row);
}

void puti(int i) {
	int digits;
	for (digits = 0;; digits++) {
		int pow = ToPower(10, digits);
		if ((i / pow) < 1) {
			break;
		}
	}

	for (int x = digits; x >= 0; x--) {
		int val;
		if (x == 0) {
			val = i;
		}
		else {
			val = i / ToPower(10, x - 1);
		}
		putc(48 + val);
		i -= val * ToPower(10, x - 1);
	}
}

void puts(char* s) {
	int size = strlen(s);
	for (int i = 0; i < size; i++) {
		putc(s[i]);
	}
}

void printf(char* format, ...) {
	int* ptr = (int*)&format + 1;

	while (*format != '\0') {
		if (*format == '%') {
			switch (*(format + 1)) {
			case 'i':
				puti(*ptr);
				ptr++;
				format++;
				break;
			case 'c':
				putc((char)*ptr);
				ptr++;
				format++;
				break;
			case 's':
				puts((char*)*ptr);
				ptr++;
				format++;
				break;
			default:
				putc(*format);
			}
		}
		else {
			putc(*format);
		}
		format++;
	}
}