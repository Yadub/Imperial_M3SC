#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int rquartic_roots(double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* -Functions-implemented-in-current-file------------------------------------- */
double f_x(double *, double);
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, 00733164, M3SC */
	print_statements();
	double  a[4],root[5];

	printf("Enter coefficients of Equation x^4+a[3]*x^3+a[2]*x^2+a[1]*x+a[0]=0\n");
	printf("in the order a, separated by spaces: ");
	scanf("%lf %lf %lf %lf",&a[3],&a[2],&a[1],&a[0]);
	printf("\n");

	int quartic_case = rquartic_roots(a,root);
	printf("case: %d\n", quartic_case);
    printf("roots: %.10g, %.10g, %.10g, %.10g\n", root[1],root[2],root[3],root[4]);
}
/* --------------------------------------------------------------------------- */

double f_x(double *a, double x){
    /* Bhageria, Yadu, 00733164, M3SC */
	return(a[3]*x*x*x + a[2]*x*x + a[1]*x + a[0]);
}
/* --------------------------------------------------------------------------- */
