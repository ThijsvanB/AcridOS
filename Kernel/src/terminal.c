#define __TERMINAL__
#include "../include/terminal.h"

char col;
char row;
char color;
char text[ROWMAX * COLMAX];

void terminalInit() {
	col = 0;
	row = 0;
	color = 0x0F;

	for (int i = 0; i < ROWMAX * COLMAX; i++) {
		text[i] = '\0';
	}
}

void setcolor(char c) {
	color = c;
}

void putc(char c) {
	sp_printf("%i %i %c\n", row, col, c);
	switch (c) {
	case '\n':	//Enter
		col = 0;
		row++;
		break;
	case 0x08:
		if (col > 0) {
			col--;
		}
		else if (row > 0) {
			col = COLMAX - 1;
			row--;
		}
		draw_char_13h(col * 8, row * 8, ' ', color);
		text[row * COLMAX + col] = c;
		break;
	default:
		draw_char_13h(col * 8, row * 8, c, color);
		text[row * COLMAX + col] = c;
		col++;
		break;
	}

	if (row == ROWMAX) {
		for (int i = 1; i < ROWMAX; i++) {
			for (int j = 0; j < COLMAX; j++) {
				text[(i - 1) * COLMAX + j] = text[i * COLMAX + j];
				draw_char_13h(j * 8, (i - 1) * 8, text[i * COLMAX + j], color);
			}
		}
		for (int i = 0; i < COLMAX; i++) {
			text[(ROWMAX - 1) * COLMAX + i] = '\0';
			draw_char_13h(i * 8, (ROWMAX - 1) * 8, '\0', color);
		}
		row--;
	}
	if (col == COLMAX) {
		col = 0;
		row++;
	}
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

int getrow() {
	return row;
}

int getcol() {
	return col;
}