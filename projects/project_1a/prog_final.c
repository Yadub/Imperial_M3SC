#include <stdio.h>
#include <math.h>

/* This version of the code deals with the case where 
a1^2 >> 4 a0 a2 or 4 a0 a2 >> a1^2 */

int lin_root(double, double, double *);
int quad_roots(double, double, double, double *, double *);

int main(void) {
	double  a2,a1,a0,r1,r2;
	int quad_case;
	printf("enter coefficients of Linear Equation a2*x^2+a1*x+a0=0\n");
	printf("in the order a2,a1,a0, seperated by spaces\n");
	scanf("%lf %lf %lf",&a2,&a1,&a0);

	quad_case = quad_roots(a2,a1,a0,&r1,&r2);
	switch (quad_case) {
		case -3: printf("The values of a2, a1, a0 were contradictory\n"); break;
		case -2: printf("a2=a1=a0=0 so any real number is a root as the equation is a tautology\n"); break;
		case -1: printf("a2=0 so we are dealing with a linear equation with one root\n r1 = %10.8g (upto 2 decimal places)\n", r1); break;
		case 0: printf("The roots are complex.\n r1 = %10.8g + i %10.8g and r2 = %10.8g - i %10.8g \n", r1,r2,r1,r2); break;
		case 1: printf("There are repeated real roots.\n r1 = r2 = %10.8g \n", r1); break;
		case 2: printf("There are two real roots.\nr1 = %10.8g and r2 = %10.8g \n", r1,r2); break;
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
	double d,dr,four=4,two=2,zero=0,one=1,dummy,a1_half,s,e;


	if (a2==0) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==0) {
		lin_root(a2,a1,r1);
		if (r1<0) {
			*r2=*r1;
			*r1=zero;
			return(2);
		} else {
			*r2=zero;
			if (*r1==zero) {return (1);} else {return(2);}
		}
	}

	a1_half = a1/two;

	if (a1_half>=a0){
		e=one-((a0/a1_half)*(a2/a1_half));
	} else {
		e=(a1_half*(a1_half/a0))-a2;
	}

	if (e<zero){ 
		*r1=(-a1_half)/(a2); //Real Part
		if (a1_half>=a0){
			*r2=fabs(a1_half)*sqrt(-e)/a2; //Imaginary part (a1_half>=a0)
		} else {*r2=sqrt(fabs(a0))*sqrt(-e)/a2;} //Imaginary part (a1_half<a0)
		return(0);
	} else if (e==zero){
		*r1=(-a1_half)/(a2);
		return(1);
	} else {
		if (a1_half>=a0){
			if (a2>zero){
				*r1=(a1_half+fabs(a1_half)*sqrt(e))/a2;
				*r2=(a1_half-fabs(a1_half)*sqrt(e))/a2;
			} else {
			*r2=(a1_half+fabs(a1_half)*sqrt(e))/a2;
			*r1=(a1_half-fabs(a1_half)*sqrt(e))/a2;				
			}
		} else{
			if (a2>zero){
				*r1=(a1_half+sqrt(fabs(a0))*sqrt(-e))/a2;
				*r2=(a1_half-sqrt(fabs(a0))*sqrt(-e))/a2;
			} else {
			*r2=(a1_half+fabs(a1_half)*sqrt(e))/a2;
			*r1=(a1_half-sqrt(fabs(a0))*sqrt(-e))/a2;				
			}
		}
	return(2);
	}


/*
	d=a1*a1-four*a2*a0;
	if (d>zero) {
		dr=sqrt(d);
		if (a1>zero) {
			if (a2>zero) {
				*r2=(-a1-dr)/(two*a2);
				*r1=two*a0/(-a1-dr);
			} else {
				*r1=(-a1-dr)/(two*a2);
				*r2=two*a0/(-a1-dr);
			}
		} else {
			if (a2>zero) {
				*r1=(-a1+dr)/(two*a2);
				*r2=two*a0/(-a1+dr);
			} else {
				*r2=(-a1+dr)/(two*a2);
				*r1=two*a0/(-a1+dr);
			}
		}
		return(2);
	} else if (d==zero){
		*r1=(-a1)/(two*a2);
		*r2=(-a1)/(two*a2);
		return(1);
	} else {
		dr=sqrt(d);
		*r1=(-a1)/(two*a2);
		*r2=(sqrt(-d))/(two*a2);
		return(0);
	}
*/
}
