#include "../include/math.h"
#include "../include/serial_port.h"

int ToPower(int num, int pow) {
	int ret = 1;
	for (int i = 0; i < pow; i++) {
		ret *= num;
	}
	sp_printf("ToPower: %i\n", ret);
	return ret;
}
