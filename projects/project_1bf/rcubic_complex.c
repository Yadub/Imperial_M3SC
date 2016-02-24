#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h> //for DBL_EPSILON

/* -Functions-needed-from-other-files----------------------------------------- */
int quad_roots(double complex,double complex,double complex,double complex *,double complex *);
/* -Functions-implemented-in-current-file------------------------------------- */
double complex iterate_z(double complex, double complex, double complex, double complex);
double complex newton_rapheson(double complex, double complex, double complex);
void order_2(double complex *, double complex *);
void order_3(double complex *, double complex *, double complex *);
int roots_return(double complex *, double complex *, double complex *);
int rcubic_roots(double complex, double complex, double complex, double complex *, double complex *, double complex *);
void direct_method(double complex, double complex, double complex, double complex *, double complex *, double complex *); //to comapre with the NR method
/* --------------------------------------------------------------------------- */

int rcubic_roots(double complex a2, double complex a1, double complex a0, double complex * r1, double complex * r2, double complex * r3){
    /* Bhageria, Yadu, M3SC */
    double complex zero=0,one=1.0;

    if (a2 == zero & a1 == zero & a0 == zero) {
        *r1=zero;
        return(1);
    } else if (a2 == zero && a1 == zero) { /* Part 3 i */
        *r1 = cpow(-a0,1.0/3.0);
        *r2 = *r1 * (0.5 + I * sqrt(3.0)/2.0);
        *r3 = *r2 * (0.5 + I * sqrt(3.0)/2.0);
    } else if (a0 == zero){
        *r1 = zero;
        quad_roots(one,a2,a1,r2,r3);
    } else if (a0==a1*a2){ /* Part 3 iii */
        *r1 = -a2;
        *r2 = csqrt(-a1);
        *r3 = -csqrt(-a1);
    } else if ( 3.0*a1==a2*a2 && 27.0*a0==a2*a2*a2 ){ /* Part 3 iv */
        *r1 = -a2/3.0;
        return(1);
    } else {
        *r1 = newton_rapheson(a2,a1,a0);
        quad_roots(one, a2+(*r1), -a0/(*r1),r2,r3);
        //direct_method(a2,a1,a0,r1,r2,r3);
    }
    return(roots_return(r1,r2,r3));
}
/* --------------------------------------------------------------------------- */

double complex iterate_z(double complex a2, double complex a1, double complex a0, double complex z){
    /* Bhageria, Yadu, M3SC */
    return(z - (z*z*z + a2*z*z + a1*z + a0)/(3.0*z*z + 2.0*a2*z + a1));
}
/* --------------------------------------------------------------------------- */

double complex newton_rapheson(double complex a2, double complex a1, double complex a0){
    /* Bhageria, Yadu, M3SC */
    double complex zn,zn1;
    int count=1;

    zn = 1.0 + I; //Set starting value
    zn1 = iterate_z(a2,a1,a0,zn);
    while (cabs(zn-zn1)>DBL_EPSILON && count<20 ){
        zn=zn1;
        zn1 = iterate_z(a2,a1,a0,zn);
        count = count + 1;
    } return(zn1);
}
/* --------------------------------------------------------------------------- */

void order_2(double complex *r1, double complex *r2){
    /* Bhageria, Yadu, M3SC */
    double complex dummy;
    if ( creal(*r1) < creal(*r2) ) {
        dummy = *r2;
        *r2 = *r1;
        *r1 = dummy;
    } else if ( creal(*r1) == creal(*r2) ){
        if ( cimag(*r1) < cimag(*r2) ){
            dummy = *r2;
            *r2 = *r1;
            *r1 = dummy;
        }
    }
}
/* --------------------------------------------------------------------------- */

void order_3(double complex *r1, double complex *r2, double complex *r3){
    /* Bhageria, Yadu, M3SC */
    order_2(r1,r3);
    order_2(r1,r2);
    order_2(r2,r3);
}
/* --------------------------------------------------------------------------- */

int roots_return(double complex *r1, double complex *r2, double complex *r3){
    /* Bhageria, Yadu, M3SC */
    order_3(r1,r2,r3);
    if (*r1==*r2 && *r2==*r3){
        return(1);
    } else {
        return (*r1==*r2) || (*r2==*r3) ? 2 : 3;
    }
}
/* --------------------------------------------------------------------------- */

void direct_method(double complex a2, double complex a1, double complex a0, double complex * r1, double complex * r2, double complex * r3){
    double complex A,B;

    //C = -2.0*a2*a2*a2 + 9.0*a2*a1 - 27.0*a0 + 3.0*sqrt(3.0)*csqrt(-a2*a2*a1*a1 + 4.0*a1*a1*a1 + 4.0*a2*a2*a2*a0 - 18.0*a2*a1*a0 + 27.0*a0*a0);
    A = cpow(-2.0*a2*a2*a2 + 9.0*a2*a1 - 27.0*a0 + 3.0*sqrt(3.0)*csqrt(-a2*a2*a1*a1 + 4.0*a1*a1*a1 + 4.0*a2*a2*a2*a0 - 18.0*a2*a1*a0 + 27.0*a0*a0),1.0/3.0)/(3.0*cbrt(2));
    B = (-a2*a2 + 3.0*a1)/(9.0*A);
    *r1 = -a2/3.0 + A - B;
    *r2 = -a2/3.0 + ((-1.0 - I * sqrt(3.0))/2.0)*A - ((-1.0 + I * sqrt(3.0))/2.0)*B;
    *r3 = -a2/3.0 + ((-1.0 + I * sqrt(3.0))/2.0)*A - ((-1.0 - I * sqrt(3.0))/2.0)*B;
}
/* --------------------------------------------------------------------------- */
