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
double *Gauss(double **, double *, int, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    int i,j, B=1;
    clock_t start, end;

    int N = 524288;

    double *Y = allocate_vector(N+1);
    for (i=1; i<N+2; i++){
        if ((double)i/N <= 0.5 && (double)i/N > 0.25){
            Y[i] = -80.0;
        } else{Y[i] = 0.0;}
    }

    double **A_banded = allocate_matrix(N+1,2*B+1);

    for (i=1; i<=N+1; i++){ //print to see what it is
        for (j=1;j<2*(B+1);j++){
            A_banded[i][j]=0.0;
        }
    }

    A_banded[1][B+1] = 1.0;
    for (i=2; i<=N; i++){
        A_banded[i][B+1] = -2.0;
        A_banded[i][B+2] = A_banded[i][B] = 1.0;
    }
    A_banded[N+1][B+1] = 1.0;

    start = clock();
    double * x = BGauss(A_banded,Y,N+1,B);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    printf("Time taken: %f\n", time_taken);

    printf("The returned vector is\n");
    for (i=1; i<N+2; i++){
            x[i] /= N*N;
    }
    print_vector(x,N+1);

}
