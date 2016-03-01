#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int rcubic_roots(double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* -Functions-implemented-in-current-file------------------------------------- */
double f_x(double *, double);
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double  a[3],root[4];
	int cubic_case;

	printf("Enter coefficients of Equation x^3+a[2]*x^2+a[1]*x+a[0]=0\n");
	printf("in the order a, separated by spaces: ");
	scanf("%lf %lf %lf",&a[2],&a[1],&a[0]);
	printf("\n");

	//double alp=0.2135,bet=0.01709,R=0.0820578,T,P;
	//P = alp/(27.0*bet*bet);
	//T = (P/R)*(sqrt(3.0*alp/P)-bet);
	//printf(" T: %f\n", T);
	//printf(" P: %f\n", P);
	//printf("\n");
	//a[2]=-bet-R*T/P;
	//a[1]=alp/P;
	//a[0]=-(alp*bet)/P;

	cubic_case = rcubic_roots(a,root);
	switch (cubic_case) {
		case 0: printf("There is one real root (root[1]) and two complex roots (root[2],root[3]).\n root[1] = %.10g, root[2] = %.10g + %.10gi, root[3] = %.10g - %.10gi \n", root[1],root[2],root[3],root[2],root[3]); printf(" f(root[1]) = %.10g\n", f_x(a,root[1])); break;
		case 1: printf("There are triple repeated real roots.\n root[1] = root[2] = root[3] = %.10g \n", root[1]); printf("f(root[1]) = %.10g\n", f_x(a,root[1])); break;
		case 2: printf("There is a pair of repeated real roots.\n root[1] = %.10g, root[2] = %.10g, root[3] = %.10g \n", root[1],root[2],root[3]); printf(" f(root[1]) = %.10g\n f(root[2]) = %.10g\n f(root[3]) = %.10g\n", f_x(a,root[1]),f_x(a,root[2]),f_x(a,root[3])); break;
        case 3: printf("There are three distinct real roots.\n root[1] = %g, root[2] = %g, root[3] = %g \n", root[1],root[2],root[3]); printf(" f(root[1]) = %.10g\n f(root[2]) = %.10g\n f(root[3]) = %.10g\n", f_x(a,root[1]),f_x(a,root[2]),f_x(a,root[3])); break;
    }
}
/* --------------------------------------------------------------------------- */

double f_x(double *a, double x){
	return(x*x*x + a[2]*x*x + a[1]*x + a[0]);
}
/* --------------------------------------------------------------------------- */
