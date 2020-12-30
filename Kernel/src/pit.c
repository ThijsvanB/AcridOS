#include "..\include\pit.h"

void set_pitfreq(int hz) {
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

int ticks = 0;
int count = 0;

void sleep(int ms) {

}

void int_pit(void) {
	
}