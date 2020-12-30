#include "../include/math.h"

int ToPower(int num, int pow) {
	int ret = num;
	for (int i = 0; i < pow; i++) {
		ret *= num;
	}
	return ret;
}
