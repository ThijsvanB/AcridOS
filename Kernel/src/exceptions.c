#include "..\include\serial_port.h"
#include "..\include\terminal.h"

void exc_def() {
	printf("Default\n");
	sp_printf("Default\n");
}

void exc_div0(void) {
	printf("division 0\n");
	sp_printf("division 0\n");
}

void exc_debug(void) {
	printf("Debug\n");
	sp_printf("Debug\n");
}

void int_NMI() {
	printf("NMI\n");
	sp_printf("NMI\n");
}

void exc_Break() {
	printf("Break\n");
	sp_printf("Break\n");
}

void exc_overflow() {
	printf("overflow\n");
	sp_printf("overflow\n");
}

void exc_BRE() {
	printf("Default\n");
	sp_printf("BRE\n");
}

void exc_InvOpc() {
	printf("Default\n");
	sp_printf("InvOpc\n");
}

void exc_DNA() {
	printf("Default\n");
	sp_printf("DNA\n");
}

void exc_DF() {
	printf("Default\n");
	sp_printf("DF\n");
}

void exc_CSO() {
	printf("Default\n");
	sp_printf("CSO\n");
}

void exc_InvTSS() {
	printf("Default\n");
	sp_printf("InvTSS\n");
}

void exc_SNP() {
	printf("Default\n");
	sp_printf("SNP\n");
}

void exc_SSF() {
	printf("Default\n");
	sp_printf("SSF\n");
}

void exc_gp(void) {
	printf("GP fault\n");
	sp_printf("GP fault");
}

void exc_PageFault() {
	printf("Default\n");
	sp_printf("PageFault\n");
}

void exc_x87FP() {
	printf("Default\n");
	sp_printf("x87FP\n");
}

void exc_Align() {
	printf("Default\n");
	sp_printf("Align\n");
}

void exc_Machine() {
	printf("Default\n");
	sp_printf("Machine\n");
}

void exc_SIMDFloat() {
	printf("Default\n");
	sp_printf("SIMDFloat\n");
}

void exc_Virt() {
	printf("Default\n");
	sp_printf("Virt\n");
}

void exc_Security() {
	printf("Default\n");
	sp_printf("Security\n");
}