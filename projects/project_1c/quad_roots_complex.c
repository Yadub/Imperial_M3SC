#include <stdio.h>
#include <math.h>
#include <complex.h>

/* -Functions-implemented-in-current-file------------------------------------- */
int lin_root(double complex, double complex, double complex *);
int quad_roots(double complex, double complex, double complex, double complex *, double complex *);
void print_statements();
/* --------------------------------------------------------------------------- */

int lin_root(double complex a1, double complex a0, double complex * r) {
	/* Bhageria, Yadu, 00733164, M3SC */
	double complex zero=0;

	if (a1==zero){
		if (a0==zero){
			return(0); // any number is a root
		} else{
			return(-1); // contradictory
		}
	} *r = -a0/a1; // real root
	return(1);
}
/* --------------------------------------------------------------------------- */

int quad_roots(double complex a2, double complex a1, double complex a0, double complex * r1, double complex * r2){
	/* Bhageria, Yadu, 00733164, M3SC */
	double complex four=4,two=2,zero=0,d,dr;

	if (a2==zero) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==zero) {
		lin_root(a2,a1,r1);
		*r2=zero;
		return(2);
	}

	d=a1*a1-four*a2*a0;
	if (d==zero) {
		*r1=(-a1)/(two*a2);
		*r2=(-a1)/(two*a2);
		return(1);
	} else {
		dr=csqrt(d);
		*r1 = (-a1-dr)/(two*a2);
		*r2 = (-a1+dr)/(two*a2);
		return(2);
	}
}
/* --------------------------------------------------------------------------- */

void print_statements(){
    /* Bhageria, Yadu, 00733164, M3SC */
    printf(  "         Name: Bhageria, Yadu");
    printf("\n          CID: 00733164");
	printf("\n  Course Code: 00733164, M3SC");
    printf("\nEmail Address: yrb13@ic.ac.uk");
    printf("\n         Time: %s ",__TIME__);
    printf("\n         Date: %s ",__DATE__);
    printf("\n \n");
}
/* --------------------------------------------------------------------------- */
