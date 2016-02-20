#include <stdio.h>
#include <math.h>
#include "lin_root.h"

/* Computes the root for a linear equation */
int lin_root(double a1, double a0, double* r) {
	/* Bhageria, Yadu, M3SC */
	if (a1==0){
		if (a0==0){
			return(0); // any number is a root
		} else{
			return(-1); // contradictory
		}
	}
	*r = a0 == 0 ? 0 : -a0/a1; // real root
	return(1);
}
