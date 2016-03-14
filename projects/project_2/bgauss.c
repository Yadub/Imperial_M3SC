#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/* Yadu Bhageria, 00733164, M3SC */
#ifdef COUNT
#define COUNTPP count++
#else
#define COUNTPP
#endif

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_vector(int);
/* -Functions-implemented-in-current-file------------------------------------- */
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

double *BGauss(double **A, double *y, int N, int B){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,k;
    double ratio;
    int count = 0;
    double *x = allocate_vector(N);
#ifdef DEBUG
    printf("DEBUG REPORT| Inputted Values (A and y)\n");
    print_vector(y,N);
    print_matrix(A,N,2*B+1);
#endif
/*
    Decompose A along wtih y
*/
    for (i=1; i<N; i++){
        for (j=1; j<B+1 && j<N+1-i; j++){
            ratio = A[i+j][B+1-j]/A[i][B+1];
            #pragma omp parallel for
            for (k=B+1-j; k<2*B+2-j; k++){
                A[i+j][k] -= ratio*A[i][j+k];
                COUNTPP;
            }
            y[i+j] -= ratio*y[i];
            COUNTPP;
        }
    }
#ifdef DEBUG
    printf("DEBUG REPORT| Converted Values (A and y)\n" );
    print_matrix(A,N,2*B+1);
    print_vector(y,N);
    printf("DEBUG REPORT| Reduction count = %d\n\n", count);
#endif
/*
Substitute back in to get x
*/
    x[N] = y[N]/A[N][B+1];
    for (i=N-1; i>0; i--){
        x[i] += y[i];
        COUNTPP;
        for (j=1; j<B+1 && j<N-i+1; j++){
            x[i] -= A[i][B+1+j]*x[i+j];
            COUNTPP;
        }
        x[i] /= A[i][B+1];
        COUNTPP;
    }
#ifdef DEBUG
    printf("DEBUG REPORT| Total count = %d\n\n", count);
#endif

return(x);
}
