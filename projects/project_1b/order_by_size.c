#include <stdio.h>
#include "order_by_size.h"

void order_by_size(double* r1, double* r2) {
	if (*r2>*r1) {
		double dummy = *r1;
		*r1 = *r2;
		*r2 = dummy;
	}
}
