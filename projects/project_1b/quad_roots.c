#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"

int quad_roots(double a2, double a1, double a0, double* r1, double* r2){
	double two=2,zero=0,one=1,a1_half,e,coef;
	int d_sgn,add_sgn;

	if (a2==0) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==0) {
		lin_root(a2,a1,r1);
		*r2 = zero;
		order_2(r1,r2);
		return *r1 == *r2 ? 1 : 2;
	}

	a1_half = a1/two;

	if (fabs(a1_half)>=fabs(a0)){
		e=one-((a0/a1_half)*(a2/a1_half));
		coef = fabs(a1_half);
		d_sgn = sgn(e);
	} else {
		e=(a1_half*(a1_half/a0))-a2;
		coef = sqrt(fabs(a0));
		d_sgn = sgn(a0)*sgn(e);
	}

	if (d_sgn==-1){
		*r1=(-a1_half)/(a2); //Real Part
		*r2=coef*sqrt(fabs(e))/a2; //Imaginary Part
		return(0);
	} else if (d_sgn==0){
		*r1=(-a1_half)/(a2);
		return(1);
	} else {
		add_sgn = a1 == zero ? 1 : sgn(a1);
		*r1=(-a1_half-add_sgn*coef*sqrt(fabs(e)))/a2;
		*r2=(a0 / *r1)/a2;
		order_2(r1,r2);
		return(2);
	}
}
