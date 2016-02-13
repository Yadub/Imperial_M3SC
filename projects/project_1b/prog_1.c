#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"

/* This version of the code deals with the case where
a1^2 >> 4 a0 a2 or 4 a0 a2 >> a1^2 */

int main(void) {
	printf("         Name: <Bhageria, Yadu>\n          CID: <00733164>\n   LIBRARY NO: <0246618471>\nEmail Address: <yrb13@ic.ac.uk>\n  Course Code: <M3SC>\n");
	double  a2,a1,a0,r1,r2;
	int quad_case;
	printf("enter coefficients of Linear Equation a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, seperated by spaces: ");
	scanf("%lf %lf %lf",&a2,&a1,&a0);

	quad_case = quad_roots(a2,a1,a0,&r1,&r2);
	switch (quad_case) {
		case -3: printf("The values of a2, a1, a0 resulted in a contradictory equation\n"); break;
		case -2: printf("a2=a1=a0=0 so any real number is a root as the equation is tautological\n"); break;
		case -1: printf("a2=0 so we are dealing with a linear equation with one root\nr1 = %.10g\n", r1); break;
		case 0: printf("The roots are complex.\nr1 = %.10g + %.10gi, r2 = %.10g - %.10gi \n", r1,r2,r1,r2); break;
		case 1: printf("There are repeated real roots.\n r1 = r2 = %.10g \n", r1); break;
		case 2: printf("There are two real roots.\nr1 = %.10g, r2 = %.10g \n", r1,r2); break;
	}
}
