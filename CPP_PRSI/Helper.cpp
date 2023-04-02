#include "Helper.h"

int Helper::randomInRange(int n)
{
	srand(time(NULL));
	return rand() % (n);
}