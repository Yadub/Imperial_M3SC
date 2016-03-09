#include <stdio.h>
#include <math.h>

/* Computes the root for a linear equation */
int lin_root(double *a, double *root) {
	/* Bhageria, Yadu, 00733164, M3SC */

	if (a[1]==0){
		if (a[0]==0){
			return(0); // any number is a root
		} else{
			return(-1); // contradictory
		}
	}
	root[1] = a[0] == 0 ? 0 : -a[0]/a[1]; // real root
	return(1);
}
