#include "..\include\serial_port.h"

void init_serial() {
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x80);
	outb(PORT + 0, 0x03);
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x03);
	outb(PORT + 2, 0xC7);
	outb(PORT + 4, 0x0B);
}

int serial_recieved() {
	return inb(PORT + 5) & 1;
}

unsigned char read_serial() {
	while (serial_recieved() == 0);

	return inb(PORT);
}

int is_transmit_empty() {
	return inb(PORT + 5) & 0x20;
}

void sp_putc(char a) {
	while (is_transmit_empty() == 0);

	outb(PORT, a);
}

void sp_puti(int i) {
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
		sp_putc(48 + val);
		i -= val * ToPower(10, x - 1);
	}
}

void sp_puts(char* s) {
	int size = strlen(s);
	for (int i = 0; i < size; i++) {
		sp_putc(s[i]);
	}
}

void sp_printf(char* format, ...) {
	int* ptr = (int*)&format + 1;

	while (*format != '\0') {
		if (*format == '%') {
			switch (*(format + 1)) {
			case 'i':
				sp_puti(*ptr);
				ptr++;
				format++;
				break;
			case 'c':
				sp_putc((char)*ptr);
				ptr++;
				format++;
				break;
			case 's':
				sp_puts((char*)*ptr);
				ptr++;
				format++;
				break;
			default:
				sp_putc(*format);
			}
		}
		else {
			sp_putc(*format);
		}
		format++;
	}
}