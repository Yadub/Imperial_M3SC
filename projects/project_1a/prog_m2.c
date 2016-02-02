#include <stdio.h>
#include <math.h>
#include <complex.h> // Standard Library of Complex Numbers

/* This version of the code deals with complex numbers and the case where a1^2 >> 4 a0 a2. */

int lin_root(double complex, double complex, double complex *);
int quad_roots(double complex, double complex, double complex, double complex *, double complex *);

int main(void) {
	double complex  a2,a1,a0,r1,r2,z;
	int quad_case,j; 
	printf("------------------------------------------------------------------\n");
	printf("|  j |       Re(w+) |       Im(w+) |       Re(w-) |       Im(w-) | \n");

	for (j=0;j<81;j=j+1) {
		printf("------------------------------------------------------------------\n");

		z = cos(j*M_PI/40.0) + I * sin(j*M_PI/40.0);
		a2 = 12.0;
		a1 = -9*z*z;
		a0 = 24*z - 8*z - 12;
		/*
		printf("a2 = %.1f%+.1fi\n", creal(a2), cimag(a2));
		printf("a1 = %.1f%+.1fi\n", creal(a1), cimag(a1));
		printf("a0 = %.1f%+.1fi\n", creal(a0), cimag(a0));
		*/
		quad_case = quad_roots(a2,a1,a0,&r1,&r2);
		switch (quad_case) {
			case -3: printf("The values of a2, a1, a0 were contradictory\n"); break;
			case -2: printf("a2=a1=a0=0 so any real number is a root as the equation is a tautology\n"); break;
			case -1: printf("a2=0 so we are dealing with a linear equation with one root\n r1 = %10.8g + %10.8gi (upto 2 decimal places)\n", creal(1),cimag(r1)); break;
			case 1: printf("There are repeated real roots.\n r1 = r2 = %10.8g \n", creal(r1)); break;
			case 2: printf("| %2d | %12.6f | %12.6f | %12.6f | %12.6f |\n", j,creal(r1),cimag(r1),creal(r2),cimag(r2)); break;
		}
	}
	printf("------------------------------------------------------------------\n");
	printf("The roots are ordered by increasing real part. i.e. re(r1) > re(r2)\n");
}

int lin_root(double complex a1, double complex a0, double complex * r) {
	double complex zero=0;

	if (a1==zero){
		if (a0==zero){
			return(0); // any number is a root
		} else{
			return(-1); // contradictory
		}
	} *r = -a0/a1; // real root
	return(1);
}

int quad_roots(double complex a2, double complex a1, double complex a0, double complex * r1, double complex * r2){
	double complex four=4,two=2,zero=0,d,dr;

	if (a2==zero) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==zero) {
		lin_root(a2,a1,r1);
		*r2=zero;
		return(2);
	}

	d=a1*a1-four*a2*a0;
	if (d==zero) {
		*r1=(-a1)/(two*a2);
		return(1);
	} else {
		dr=csqrt(d);
		*r1 = (-a1+dr)/(two*a2);
		*r2 = (-a1-dr)/(two*a2);
	} return(2);
}
