#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"
#include "rcubic_roots.h"
#include "print_statements.h"

/* This version of the code deals with the case where
a1^2 >> 4 a0 a2 or 4 a0 a2 >> a1^2 */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double  a2,a1,a0,r1,r2,r3;
	int cubic_case;
	printf("Enter coefficients of Equation x^3+a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, seperated by spaces: ");
	scanf("%lf %lf %lf",&a2,&a1,&a0);

	cubic_case = rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
	switch (cubic_case) {
		case 0: printf("There is one real root (r1) and two complex roots (r2,r3).\n r1 = %.10g, r2 = %.10g + %.10gi, r3 = %.10g - %.10gi \n", r1,r2,r3,r2,r3); break;
		case 1: printf("There are triple repeated real roots.\n r1 = r2 = r3 = %.10g \n", r1); break;
		case 2: printf("There is a pair of repeated real roots.\n r1 = %.10g, r2 = %.10g, r3 = %.10g \n", r1,r2,r3); break;
        case 3: printf("There are three distinct real roots.\n r1 = %g, r2 = %g, r3 = %g \n", r1,r2,r3); break;
    }
}
