#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int rcubic_roots(double, double, double, double *, double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* -Functions-implemented-in-current-file------------------------------------- */
double f_x(double, double, double, double);
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double  a2,a1,a0,r1,r2,r3;
	int cubic_case;
	printf("Enter coefficients of Equation x^3+a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, separated by spaces: ");
	scanf("%lf %lf %lf",&a2,&a1,&a0);
	printf("\n");

	cubic_case = rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
	switch (cubic_case) {
		case 0: printf("There is one real root (r1) and two complex roots (r2,r3).\n r1 = %.10g, r2 = %.10g + %.10gi, r3 = %.10g - %.10gi \n", r1,r2,r3,r2,r3); printf(" f(r1) = %.10g\n", f_x(a2,a1,a0,r1)); break;
		case 1: printf("There are triple repeated real roots.\n r1 = r2 = r3 = %.10g \n", r1); printf("f(r1) = %.10g\n", f_x(a2,a1,a0,r1)); break;
		case 2: printf("There is a pair of repeated real roots.\n r1 = %.10g, r2 = %.10g, r3 = %.10g \n", r1,r2,r3); printf(" f(r1) = %.10g\n f(r2) = %.10g\n f(r3) = %.10g\n", f_x(a2,a1,a0,r1),f_x(a2,a1,a0,r2),f_x(a2,a1,a0,r3)); break;
        case 3: printf("There are three distinct real roots.\n r1 = %g, r2 = %g, r3 = %g \n", r1,r2,r3); printf(" f(r1) = %.10g\n f(r2) = %.10g\n f(r3) = %.10g\n", f_x(a2,a1,a0,r1),f_x(a2,a1,a0,r2),f_x(a2,a1,a0,r3)); break;
    }
}
/* --------------------------------------------------------------------------- */

double f_x(double a2, double a1, double a0, double x){
	return(x*x*x + a2*x*x + a1*x + a0);
}
/* --------------------------------------------------------------------------- */
