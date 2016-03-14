#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_vector(int);
double **allocate_matrix(int, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    int N = 3, B = 1;
    int i,j;
    clock_t start, end;

    double *Y = allocate_vector(N);
    Y[1] = Y[2] = Y[3] = 2;

    double **A = allocate_matrix(N,2*B+1);

    for (i=1; i<=N; i++){ //print to see what it is
        for (j=1;j<N+1;j++){
            A[i][j]=0.0;
        }
    }
    A[3][2] =  A[2][2] = A[1][2] = -2.0;
    A[2][3] = A[2][1] =  A[3][1] =  A[1][3] = 1;

    start = clock();
    double * x = BGauss(A,Y,N,B);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    printf("Time taken: %f\n", time_taken);

    printf("The returned vector is\n");
    print_vector(x,N);
}
