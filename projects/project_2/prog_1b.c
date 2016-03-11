#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
double *allocate_vector(int);
double **allocate_matrix(int);
double *Gauss(double **, double *, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    double N = 8;
    int i,j;

    double *Y = allocate_vector(N);
    for (i=1; i<N+1; i++){
        Y[i] = i;
    }

    double **A = allocate_matrix(N);

    for (i=1; i<=N; i++){ //print to see what it is
        for (j=1;j<N+1;j++){
            A[i][j]=0.0;
        }
    }
    for (i=1; i<=N; i++){
        A[i][i] = 6.0;
        if (i!=N){
            A[i][i+1] = -4.0;
            A[i+1][i] = -4.0;
        }
        if (i<N-1){
            A[i][i+2] = 1.0;
            A[i+2][i] = 1.0;
        }
    }
    A[1][1] = 5.0;
    A[7][7] = 7.0;
    A[8][8] = 6.0;
    A[8][7] =-8.0;

    A[8][6] = 2.0;

    double * x = Gauss(A,Y,N);

    printf("The returned vector is\n");
    print_vector(x,N);

}
