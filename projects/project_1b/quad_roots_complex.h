#include <complex.h>
#ifndef QUAD_ROOTS_COMPLEX
#define QUAD_ROOTS_COMPLEX //include guards

/* Compute the roots of a quadratic equation */
int lin_root(double complex a1, double complex a0, double complex * r);
int quad_roots(double complex a2, double complex a1, double complex a0, double complex * r1, double complex * r2);

#endif /* QUAD_ROOTS_COMPLEX */
