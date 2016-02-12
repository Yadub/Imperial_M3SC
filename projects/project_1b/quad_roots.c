#include <stdio.h>
#include <math.h>
#include "order_by_size.h"
#include "lin_root.h"
#include "quad_roots.h"

int quad_roots(double a2, double a1, double a0, double* r1, double* r2){
	double two=2,zero=0,one=1,a1_half,e;

	if (a2==0) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==0) {
		lin_root(a2,a1,r1);
		if (r1<0) {
			if (*r1==zero) {return (1);}
			else {
				*r2=zero;
				order_by_size(r1,r2);
				return(2);
			}
		}
	}

	a1_half = a1/two;

	if (fabs(a1_half)>=fabs(a0)){
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
			if (a1>zero) {
				*r1=(-a1_half-fabs(a1_half)*sqrt(e))/a2;
				*r2=(a0 / *r1)/a2;
			} else {
				*r1=(-a1_half+fabs(a1_half)*sqrt(e))/a2;
				*r2=(a0 / *r1)/a2;
			}
		} else{
			if (a1>zero) {
				*r1=(-a1_half-sqrt(fabs(a0))*sqrt(-e))/a2;
				*r2=(a0 / *r1)/a2;
			} else {
				*r1=(-a1_half+sqrt(fabs(a0))*sqrt(-e))/a2;
				*r2=(a0 / *r1)/a2;
			}
		}
	order_by_size(r1,r2);
	return(2);
	}
}
