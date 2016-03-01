#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int lin_root(double *,double *);
/* -Functions-implemented-in-current-file------------------------------------- */
int sgn(double);
void order(double *);
int quad_roots(double *, double *);
void print_statements();
/* --------------------------------------------------------------------------- */

int quad_roots(double *a, double * root){
	/* Bhageria, Yadu, M3SC */
	double two=2,zero=0,one=1,a1_half,e,coef;
	int d_sgn,add_sgn;

	if (a[2]==0) {
		return (-2 + lin_root(a,root));
	} else if (a[0]==0) {
		lin_root(a,root);
		root[2] = zero;
		order(root);
		return root[1] == root[2] ? 1 : 2;
	}

	a1_half = a[1]/two;

	if (fabs(a1_half)>=fabs(a[0])){
		e=one-((a[0]/a1_half)*(a[2]/a1_half));
		coef = fabs(a1_half);
		d_sgn = sgn(e);
	} else {
		e=(a1_half*(a1_half/a[0]))-a[2];
		coef = sqrt(fabs(a[0]));
		d_sgn = sgn(a[0])*sgn(e);
	}

	if (d_sgn==-1){
		root[1]=(-a1_half)/(a[2]); //Real Part
		root[2]=coef*sqrt(fabs(e))/a[2]; //Imaginary Part
		return(0);
	} else if (d_sgn==0){
		root[1]=(-a1_half)/(a[2]);
		root[2]=(-a1_half)/(a[2]);
		return(1);
	} else {
		add_sgn = a[1] == zero ? 1 : sgn(a[1]);
		root[1]=(-a1_half-add_sgn*coef*sqrt(fabs(e)))/a[2];
		root[2]=(a[0] / root[1])/a[2];
		order(root);
		return(2);
	}
}
/* --------------------------------------------------------------------------- */

void order(double * nums) {
	/* Bhageria, Yadu, M3SC */
	int i,j,n = sizeof(nums);
	for (i=0;i<n;i++){
		for(j=0;j<n-i;j++){
			if (nums[j] < nums[j+1]) {
				double dummy = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = dummy;
			}
		}
	}
}
/* --------------------------------------------------------------------------- */

int sgn(double x){
	/* Bhageria, Yadu, M3SC */
	double zero = 0;
	if (x<zero){return(-1);}
	else if (x>zero){return(1);}
	return(0);
}
/* --------------------------------------------------------------------------- */

void print_statements(){
    /* Bhageria, Yadu, M3SC */
    printf(  "         Name: Bhageria, Yadu");
    printf("\n          CID: 00733164");
	printf("\n  Course Code: M3SC");
    printf("\nEmail Address: yrb13@ic.ac.uk");
    printf("\n         Time: %s ",__TIME__);
    printf("\n         Date: %s ",__DATE__);
    printf("\n \n");
    }
/* --------------------------------------------------------------------------- */
