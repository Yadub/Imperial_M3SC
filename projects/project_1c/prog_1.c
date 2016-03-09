#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int lin_root(double *, double *);
int quad_roots(double *, double *);
int rcubic_roots(double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, 00733164, M3SC */
	print_statements();
	double  a[3],root[4];
	int lin_case, quad_case, cubic_case, poly;

	printf("Choose the degree of polynomial to be tested (1,2,3): ");
	scanf("%d", &poly);
	printf("\n");

	switch (poly){
		case 1: {
		printf("Enter coefficients of Equation a[1]*x+a[0]=0\n");
		printf("in the order a[1], a[0], separated by spaces: ");
		scanf("%lf %lf",&a[1],&a[0]);
		printf("\n");
		lin_case = lin_root(a,root);
		printf("Lin_case: %d\n", lin_case);
		printf("    Root: %g\n", root[1]);
		break;}

		case 2: {
		printf("Enter coefficients of Equation a[2]*x^2+a[1]*x+a[0]=0\n");
		printf("in the order a[2], a[1], a[0], separated by spaces: ");
		scanf("%lf %lf %lf",&a[2],&a[1],&a[0]);
		printf("\n");
		quad_case = quad_roots(a,root);
		printf("Quad_case: %d\n", quad_case);
		printf("    Roots: %g %g\n", root[1], root[2]);
		break;}

		case 3: {
		printf("Enter coefficients of Equation x^3+a[2]*x^2+a[1]*x+a[0]=0\n");
		printf("in the order a, separated by spaces: ");
		scanf("%lf %lf %lf",&a[2],&a[1],&a[0]);
		printf("\n");
		cubic_case = rcubic_roots(a,root);
		printf("Cubic_case: %d\n", cubic_case);
		printf("     Roots: %g %g %g\n", root[1], root[2], root[3]);
		break;}

	}
}
/* --------------------------------------------------------------------------- */
