#include <stdio.h>
#include "order_nums.h"

void order_2(double* r1, double* r2) {
	if (*r2>*r1) {
		double dummy = *r1;
		*r1 = *r2;
		*r2 = dummy;
	}
}

void order_3(double *r1, double *r2, double *r3) {
    order_2(r1,r3);
    order_2(r1,r2);
    order_2(r2,r3);
}
