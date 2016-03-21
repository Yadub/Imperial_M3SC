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
double *allocate_zero_vector(int);
void free_matrix(double **);
/* -Functions-implemented-in-current-file------------------------------------- */
double *Gauss(double **, double *, int);
/* --------------------------------------------------------------------------- */

double *Gauss(double **A, double *y, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    int count = 0;
    double *x = allocate_zero_vector(N);
#ifdef DEBUG
    printf("\nDEBUG REPORT| Inputted Values (A and y)\n");
    print_vector(y,N);
    print_matrix(A,N,N);
#endif
/*
    Decompose A along with y
*/

    for (i=1; i<N; i++){
        if (A[i][i]==0){
            printf("ERROR| Zero on the diagonal of A during Guassian Elimiation. Considering it as singular and exitting.\n");
            exit(-1);
        }
        #pragma omp parallel for
        for (j=i+1; j<N+1; j++){
            if (A[j][i]!=0){
                double ratio = A[j][i]/A[i][i];
                for (int k=1; k<N+1; k++){
                    A[j][k] -= ratio*A[i][k];
                    COUNTPP;
                }
                y[j] -= ratio*y[i];
                COUNTPP;
            }
        }
    }
/*
    Substitute back in to get x
*/
#ifdef DEBUG
    printf("DEBUG REPORT| Converted Values (A and y)\n" );
    print_matrix(A,N,N);
    print_vector(y,N);
    printf("DEBUG REPORT| Reduction count = %d\n\n", count);
#endif
    x[N] = y[N]/A[N][N];
    COUNTPP;
    for (i=N-1; i>0; i--){
        x[i] += y[i];
        COUNTPP;
        for (j=N; j>i; j--){
            x[i] -= A[i][j]*x[j];
            COUNTPP;
        }
        x[i] /= A[i][i];
        COUNTPP;
    }
#ifdef COUNT
    printf("DEBUG REPORT| count = %d\n\n", count);
#endif
    return(x);
}
