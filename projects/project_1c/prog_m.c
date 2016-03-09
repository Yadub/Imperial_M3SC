#include <stdio.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI /*incase Pi is not defined on a compiler */
#    define M_PI 3.14159265358979323846
#endif

/* -Functions-needed-from-other-files----------------------------------------- */
int rquartic_roots(double complex, double complex, double complex, double complex, double complex *, double complex *, double complex *, double complex *);
void print_statements();
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, 00733164, M3SC */
	print_statements();
	double complex d4,d3,d2,d1,d0,r1,r2,r3,r4,sj;
	int j;

	printf("  j,   Re(z1),    Im(z1),    Re(z2),    Im(z2),    Re(z3),    Im(z3),    Re(z4),    Im(z4)\n");

	for (j=0;j<161;j++) {
		sj = cos(j*M_PI/80.0) + I * sin(j*M_PI/80.0);
		d4 = 4*sj-2;
		d0 = -27*sj*(sj-1)/d4;
		d1 = -9*(5*sj+1)/d4;
		d2 = 3*(5*sj+1)/d4;
		d3 = -(2+4*sj)/d4;

		rquartic_roots(d3,d2,d1,d0,&r1,&r2,&r3,&r4);
		printf("%3d,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f\n", j,creal(r1),cimag(r1),creal(r2),cimag(r2),creal(r3),cimag(r3),creal(r4),cimag(r4));
	}
}
/* --------------------------------------------------------------------------- */
