#include <stdio.h>
#include <math.h>

int lin_root(double, double, double *);
int quad_roots(double, double, double, double *, double *);

int main(void) {
	printf("         Name: <Bhageria, Yadu>\n          CID: <00733164>\n   LIBRARY NO: <0246618471>\nEmail Address: <yrb13@ic.ac.uk>\n  Course Code: <M3SC>\n");
	double  a2,a1,a0,r1,r2;
	int quad_case;
	printf("Enter coefficients of Linear Equation a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, separated by spaces: ");
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

int lin_root(double a1, double a0, double* r) {
	if (a1==0){
		if (a0==0){
			return(0); // any number is a root
		} else{
			return(-1); // contradictory
		}
	}
	*r = -a0/a1; // real root
	return(1);
}

int quad_roots(double a2, double a1, double a0, double* r1, double* r2){
	double d,dr,four=4,two=2,zero=0;

	if (a2==zero) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==zero) {
		lin_root(a2,a1,r1);
		if (r1<0) {
			*r2=*r1;
			*r1=zero;
			return(2);
		} else {
			if (*r1==0) {return (1);} 
			else {
				*r2=zero;
				return(2);
			}
		}
	}

	d=a1*a1-four*a2*a0;
	if (d>zero) {
		dr=sqrt(d);
		if (a2>zero) {
			*r1=(-a1+dr)/(two*a2);
			*r2=(-a1-dr)/(two*a2);
		} else {
			*r1=(-a1-dr)/(two*a2);
			*r2=(-a1+dr)/(two*a2);
		}
		return(2);
	}
	else if (d==zero){
		*r1=(-a1)/(two*a2);
		*r2=(-a1)/(two*a2);
		return(1);
	}
	else {
		dr=sqrt(d);
		*r1=(-a1)/(two*a2);
		*r2=(sqrt(-d))/(two*fabs(a2));
		return(0);
	}
}