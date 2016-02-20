#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "quad_roots_complex.h"
#include "print_statements.h"

int rcubic_roots(double complex, double complex, double complex, double complex *, double complex *, double complex *);

/* This version of the code deals with the case where
a1^2 >> 4 a0 a2 or 4 a0 a2 >> a1^2 */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double complex  a2,a1,a0,r1,r2,r3;
    double r2real,r2imag,r1real,r1imag,r0real,r0imag;
	int cubic_case;
	
	printf("Enter coefficients of Equation x^3+a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, seperated by spaces: ");
	scanf("%lf %lf %lf %lf %lf %lf",&r2real,&r2imag,&r1real,&r1imag,&r0real,&r0imag);

    a2 = r2real + I * r2imag;
    a1 = r1real + I * r1imag;
    a0 = r0real + I * r0imag;

    printf("a2: %f + %fi\n",creal(a2),cimag(a2));
    printf("a1: %f + %fi\n",creal(a1),cimag(a1));
    printf("a0: %f + %fi\n",creal(a0),cimag(a0));

	cubic_case = rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
	switch (cubic_case) {
		case 0: printf("There is one real root (r1) and two complex roots (r2,r3).\n r1 = %.10g + %.10gi, r2 = %.10g + %.10gi, r3 = %.10g - %.10gi \n", creal(r1),cimag(r1),creal(r2),cimag(r2),creal(r3),cimag(r3)); break;
		case 1: printf("There are triple repeated real roots.\n r1 = r2 = r3 = %.10g + %.10gi \n", creal(r1), cimag(r2)); break;
		case 2: printf("There is a pair of repeated real roots.\n r1 = %.10g + %.10gi, r2 = %.10g + %.10gi, r3 = %.10g + %.10gi \n", creal(r1),cimag(r1),creal(r2),cimag(r2),creal(r3),cimag(r3)); break;
        case 3: printf("There are three distinct real roots.\n r1 = %.10g + %.10gi, r2 = %.10g + %.10gi, r3 = %.10g + %.10gi \n", creal(r1),cimag(r1),creal(r2),cimag(r2),creal(r3),cimag(r3)); break;
    }
}
