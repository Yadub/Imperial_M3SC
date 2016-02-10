#include <math.h>
#include <stdio.h>

/* 
This version of the code deals with the case where a1^2 >> 4 a0 a2. 
I have also tried to implement a function that can easily swap between floats 
and double precision numbers and also between the new and old method.
*/

//#define AS_FLOAT float; //coment out to change precision from float to double.

#ifdef AS_FLOAT
	#define REAL_VAR float
	#define SQRT sqrtf
	#define SCANF scanf("%f %f %f",&a2,&a1,&a0)
#else
	#define REAL_VAR double
	#define SQRT sqrt
	#define SCANF scanf("%lf %lf %lf",&a2,&a1,&a0)
#endif	

int lin_root(REAL_VAR, REAL_VAR, REAL_VAR *);
int quad_roots(REAL_VAR, REAL_VAR, REAL_VAR, REAL_VAR *, REAL_VAR *);
int quad_roots_old(REAL_VAR, REAL_VAR, REAL_VAR, REAL_VAR *, REAL_VAR *);

int main(void) {
	REAL_VAR  a2,a1,a0,r1,r2;
	int quad_case;

	while (a2!=99 & a1!=99 & a0!=99){
		//printf("enter coefficients of Linear Equation a2*x^2+a1*x+a0=0\n");
		//printf("in the order a2,a1,a0, seperated by spaces\n");
		SCANF;
		/*
		printf("a2 = %f\n",a2);
		printf("a1 = %f\n",a1);
		printf("a0 = %f\n",a0);
		*/

		//Comment out either depending on which method wants to be used
		quad_case = quad_roots(a2,a1,a0,&r1,&r2);
		//quad_case = quad_roots_old(a2,a1,a0,&r1,&r2);
		switch (quad_case) {
			case -3: printf("The values of a2, a1, a0 resulted in a contradictory equation\n"); break;
			case -2: printf("a2=a1=a0=0 so any real number is a root as the equation is tautological\n"); break;
			case -1: printf("a2=0 so we are dealing with a linear equation with one root\nr1 = %.10g\n", r1); break;
			case 0: printf("The roots are complex.\nr1 = %.10g + %.10gi, r2 = %.10g - %.10gi \n", r1,r2,r1,r2); break;
			case 1: printf("There are repeated real roots.\n r1 = r2 = %.10g \n", r1); break;
			case 2: /*printf("r1 = %g and r2 = %g \n \n", r1,r2);*/ printf("%.10g\n", r1); break; //the new printf statement is implemented as we are only interested in the postive root in a simple format.
		}
	}
}

int lin_root(REAL_VAR a1, REAL_VAR a0, REAL_VAR* r) {
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

int quad_roots(REAL_VAR a2, REAL_VAR a1, REAL_VAR a0, REAL_VAR* r1, REAL_VAR* r2){
	REAL_VAR d,dr,four=4,two=2,zero=0,dummy;

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

	d=a1*a1-four*a2*a0;
	if (d>zero) {
		dr=SQRT(d);
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
		*r1=(-a1)/(two*a2); //real part
		*r2=(SQRT(-d))/(two*fabs(a2)); //imaginary part (positive)
		return(0);
	}
}

//included the old quad roots code to make it easier to output values.
int quad_roots_old(REAL_VAR a2, REAL_VAR a1, REAL_VAR a0, REAL_VAR* r1, REAL_VAR* r2){
	REAL_VAR d,dr,four=4,two=2,zero=0,dummy;

	if (a2==0) {
		return (-2 + lin_root(a1,a0,r1));
	} else if (a0==0) {
		lin_root(a2,a1,r1);
		if (r1<0) {
			*r2=*r1;
			*r1=zero;
			return(2);
		} else {
			if (*r1==zero) {return (1);} 
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