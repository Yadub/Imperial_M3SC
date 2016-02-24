#include <stdio.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI /*incase Pi is not defined on a compiler */
#    define M_PI 3.14159265358979323846
#endif

/* -Functions-needed-from-other-files----------------------------------------- */
int rcubic_roots(double complex, double complex, double complex, double complex *, double complex *, double complex *);
void print_statements();
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double complex  a2,a1,a0,r1,r2,r3,sj;
	int j;

	printf("  j,   Re(z1),    Im(z1),    Re(z2),    Im(z2),    Re(z3),    Im(z3)\n");

	for (j=0;j<101;j++) {
		sj = cos(j*M_PI/50.0) + I * sin(j*M_PI/50.0);
		a0 = (18.0*sj*sj - 18*sj) / (3.0*sj -1.0);
		a1 = (30.0*sj + 6.0) / (3.0*sj - 1.0);
		a2 = -(8.0*sj + 4.0) / (3.0*sj - 1.0);
		/*
		printf("a2 = %.1f%+.1fi\n", creal(a2), cimag(a2));
		printf("a1 = %.1f%+.1fi\n", creal(a1), cimag(a1));
		printf("a0 = %.1f%+.1fi\n", creal(a0), cimag(a0));
		*/
		rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
		printf("%3d,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f,%10.6f\n", j,creal(r1),cimag(r1),creal(r2),cimag(r2),creal(r3),cimag(r3));
	}
}
/* --------------------------------------------------------------------------- */
