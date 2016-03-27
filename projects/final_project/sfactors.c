/* Yadu Bhageria, 00733164, M3SC */
#include <stdio.h>
#include <math.h>
/*incase Pi is not defined */
#ifndef M_PI
#    define M_PI acos(-1.);
#endif
/* -Functions-needed-from-other-files----------------------------------------- */
double *allocate_vector(int);
/* -Functions-implemented-in-current-file------------------------------------- */
double *SFactors(int);
/* --------------------------------------------------------------------------- */
double *SFactors(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double numerator = 1., denominator = 1.;
    double *factors = allocate_vector(N/2);

    for (int i=1; i<=N/2; i++){
        if (numerator/denominator > 1./2.){
            numerator = 1.;
            denominator *= 2.;
        }
        factors[i] = sin(M_PI*numerator/denominator);
        numerator += 2.;
    }
    return factors;
}
/* --------------------------------------------------------------------------- */
