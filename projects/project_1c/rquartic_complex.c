#include <float.h> //for DBL_EPSILON
#include <stdio.h>
#include <math.h>
#include <complex.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int quad_roots(double complex, double complex, double complex, double complex *, double complex *);
int rcubic_roots(double complex, double complex, double complex, double complex *, double complex *, double complex *);
/* -Functions-implemented-in-current-file------------------------------------- */
int rquartic_roots(double complex, double complex, double complex, double complex, double complex *, double complex *, double complex *, double complex *);
/* --------------------------------------------------------------------------- */


int rquartic_roots(double complex a3, double complex a2, double complex a1, double complex a0, double complex *r1, double complex *r2, double complex *r3, double complex *r4){
    /* Bhageria, Yadu, 00733164, M3SC */
    int qc1, qc2;
    double complex zero = 0;
    double epsilon = 1e-5;

/* Optimization Cases that Skip the R-Quartic Method */
    if (a0==zero){
        *r1 = 0;
        qc1 = rcubic_roots(a3,a2,a1,r2,r3,r4);
        if (*r1 == *r2 || *r1 == *r2 || *r1 == *r3){
            if (qc1 == 1){
                return 0;
            }
            return 2;
        }
        return 4;
    }
    else if (a3==zero && a2==zero && a1==zero) {
        *r1 = csqrt(csqrt(-a1));
        *r2 = csqrt(-csqrt(-a1));
        *r3 = -csqrt(csqrt(-a1));
        *r4 = -csqrt(-csqrt(-a1));
        return 4;
    } /* Part ii */
    else if (a3==zero && a1==zero){
        qc1 = quad_roots(1.0,a2,a0,r1,r2);
        *r3 = csqrt(*r1);
        *r4 = -csqrt(*r2);
        if (qc1==1){
            *r1 = *r3;
            *r2 = *r4;
            return 2;
        }
        *r1 = - *r3;
        *r2 = - *r4;
        return 4;
    }
/* -------------------------------------------- */

    double complex coefs_q1[3],coefs_q2[3];
    coefs_q1[2] = coefs_q2[2] = 1.0;

    double complex b[] = {4.0*a0*a2 - a1*a1 - a0*a3*a3 , a1*a3 - 4.0*a0 , -a2};
    rcubic_roots(b[2],b[1],b[0],r1,r2,r3);
    double complex r = *r1;
    if (cabs(*r2) > cabs(*r1) && cabs(*r2) > cabs(*r3)){
        r = *r2;
    } else if (cabs(*r3) > cabs(*r1) && cabs(*r3) > cabs(*r2)){
        r = *r3;
    }

    double complex v0_coef = csqrt( (r/2.0)*(r/2.0) - a0 );
    double complex v1_coef = csqrt(a3*a3/4.0 + r - a2);
    double complex a1_comparison = (r/2.0 + v0_coef)*(a3/2.0 - v1_coef) + (a3/2.0 + v1_coef)*(r/2.0 - v0_coef);

    if (cabs(a1 - a1_comparison) < epsilon){
        coefs_q1[0] = r/2.0 + v0_coef , coefs_q1[1] = a3/2.0 + v1_coef;
        coefs_q2[0] = r/2.0 - v0_coef , coefs_q2[1] = a3/2.0 - v1_coef;
    } else {
        coefs_q1[0] = r/2.0 + v0_coef , coefs_q1[1] = a3/2.0 - v1_coef;
        coefs_q2[0] = r/2.0 - v0_coef , coefs_q2[1] = a3/2.0 + v1_coef;
    }

    qc1 = quad_roots(coefs_q1[2],coefs_q1[1],coefs_q1[0],r1,r2);
    qc2 = quad_roots(coefs_q2[2],coefs_q2[1],coefs_q2[0],r3,r4);
    return (qc1 == 1 && qc2) == 1 ? 0 : (qc1 == 1 || qc2 == 1) ? 2 : 4;

}
