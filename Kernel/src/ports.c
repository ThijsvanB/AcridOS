#include "../include/ports.h"

void outb(unsigned short port, unsigned char val) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void outl(unsigned short port, unsigned int val) {
	asm volatile("outl %%eax, %%dx" : : "d"(port), "a"(val));
}

unsigned char inb(unsigned short port) {
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

unsigned int inl(unsigned short port) {
	unsigned int ret;
	asm volatile("inl %%dx, %%eax" : "=a"(ret) : "d"(port));
	return ret;
}