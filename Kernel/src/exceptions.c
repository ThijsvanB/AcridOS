#include "..\include\serial_port.h"
#include "..\include\terminal.h"

void int_def() {
	printf("Default\n");
	sp_printf("Default\n");
}

void int_div0(void) {
	printf("division 0\n");
	sp_printf("division 0\n");
}

void int_gp() {
	printf("GP fault\n");
	sp_printf("GP fault\n");
}