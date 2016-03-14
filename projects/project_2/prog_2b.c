#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_vector(int);
double **allocate_matrix(int,int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    int N = 8, B = 2;
    int i,j;
    clock_t start, end;

    double *Y = allocate_vector(N);
    for (i=1; i<N+1; i++){
        Y[i] = i;
    }

    double **A = allocate_matrix(N,2*B+1);

    for (i=1; i<=N; i++){ //print to see what it is
        for (j=1;j<2*(B+1);j++){
            A[i][j]=0.0;
        }
    }
    for (i=1; i<=N; i++){
        A[i][B+1] = 6.0;
        A[i][B+2] = A[i][B] = -4.0;
        A[i][B-1] = A[i][B+3] = 1.0;
    }
    A[1][B+1] = 5.0;
    A[7][B+1] = 7.0;
    A[8][B-1] = 2.0;
    A[8][B] = -8.0;

    start = clock();
    double * x = BGauss(A,Y,N,B);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    printf("Time taken: %f\n", time_taken);

    printf("The returned vector is\n");
    print_vector(x,N);
}
