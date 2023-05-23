#include "..\include\serial_port.h"
#include "..\include\terminal.h"

void exc_def() {
	sp_printf("Default\n");
}

void exc_div0(void) {
	sp_printf("division 0\n");
}

void exc_debug(void) {
	sp_printf("Debug\n");
}

void int_NMI() {
	sp_printf("NMI\n");
}

void exc_Break() {
	sp_printf("Break\n");
}

void exc_overflow() {
	sp_printf("overflow\n");
}

void exc_BRE() {
	sp_printf("BRE\n");
}

void exc_InvOpc() {
	sp_printf("InvOpc\n");
}

void exc_DNA() {
	sp_printf("DNA\n");
}

void exc_DF() {
	sp_printf("DF\n");
}

void exc_CSO() {
	sp_printf("CSO\n");
}

void exc_InvTSS() {
	sp_printf("InvTSS\n");
}

void exc_SNP() {
	sp_printf("SNP\n");
}

void exc_SSF() {
	sp_printf("SSF\n");
}

void exc_gp(void) {
	sp_printf("GP fault");
}

void exc_PageFault() {
	sp_printf("PageFault\n");
}

void exc_x87FP() {
	sp_printf("x87FP\n");
}

void exc_Align() {
	sp_printf("Align\n");
}

void exc_Machine() {
	sp_printf("Machine\n");
}

void exc_SIMDFloat() {
	sp_printf("SIMDFloat\n");
}

void exc_Virt() {
	sp_printf("Virt\n");
}

void exc_Security() {
	sp_printf("Security\n");
}