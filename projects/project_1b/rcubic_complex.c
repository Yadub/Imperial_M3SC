#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "quad_roots_complex.h"

int quad_roots(double complex,double complex,double complex,double complex *,double complex *);

double complex set_starting_z(double complex, double complex, double complex);
double complex iterate_z(double complex, double complex, double complex, double complex);
double complex newton_rapheson(double complex, double complex, double complex);
void order_2(double complex *, double complex *);
void order_3(double complex *, double complex *, double complex *);
int roots_return(double complex *, double complex *, double complex *);
int rcubic_roots(double complex, double complex, double complex, double complex *, double complex *, double complex *);

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
        quad_roots(one, a2+(*r1), a1/(*r1),r2,r3);
    }
    return(roots_return(r1,r2,r3));
}

double complex set_starting_z(double complex a2, double complex a1, double complex a0){
    /* Bhageria, Yadu, M3SC */
    return(a2+a1+a0);
}

double complex iterate_z(double complex a2, double complex a1, double complex a0, double complex z){
    /* Bhageria, Yadu, M3SC */
    return(z - (z*z*z + a2*z*z + a1+z + a0)/(3.0*z*z + 2.0*a2*z + a1));
}

double complex newton_rapheson(double complex a2, double complex a1, double complex a0){
    /* Bhageria, Yadu, M3SC */
    double complex zn,zn1;
    double diff, diff1;
    int count=1;

    zn = set_starting_z(a2,a1,a0);
    zn1 = iterate_z(a2,a1,a0,zn);
    while (zn!=zn1 && ( count<4 || diff1 < diff )){
        zn=zn1;
        zn1 = iterate_z(a2,a1,a0,zn);
        diff1 = cabs(zn-zn1);
        diff = diff1;
        count = count + 1;
    }
    return(zn1);
}

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

void order_3(double complex *r1, double complex *r2, double complex *r3){
    /* Bhageria, Yadu, M3SC */
    order_2(r1,r3);
    order_2(r2,r3);
    order_2(r2,r3);
}

int roots_return(double complex *r1, double complex *r2, double complex *r3){
    /* Bhageria, Yadu, M3SC */
    order_3(r1,r2,r3);
    if (*r1==*r2 && *r2==*r3){
        return(1);
    } else if (*r1==*r2){
        return(2);
    } else if (*r2==*r3){
        return(2);
    } else {
        return(3);
    }
}
