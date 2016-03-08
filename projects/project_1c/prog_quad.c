#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int quad_roots(double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, 00733164, M3SC */
	print_statements();
	double  a[3],root[3];
	int quad_case;
	printf("Enter coefficients of Linear Equation a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, seperated by spaces: ");
	scanf("%lf %lf %lf",&a[2],&a[1],&a[0]);

	quad_case = quad_roots(a,root);
	switch (quad_case) {
		case -3: printf("The values of a2, a1, a0 resulted in a contradictory equation\n"); break;
		case -2: printf("a2=a1=a0=0 so any real number is a root as the equation is tautological\n"); break;
		case -1: printf("a2=0 so we are dealing with a linear equation with one root\nr1 = %.20g\n", root[1]); break;
		case 0: printf("The roots are complex.\nr1 = %.20g + %.20gi, r2 = %.20g - %.20gi \n", root[1],root[2],root[1],root[2]); break;
		case 1: printf("There are repeated real roots.\n r1 = r2 = %.20g \n", root[1]); break;
		case 2: printf("There are two real roots.\nr1 = %.20g, r2 = %.20g \n", root[1],root[2]); break;
	}
}
/* --------------------------------------------------------------------------- */
