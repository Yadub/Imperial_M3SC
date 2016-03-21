#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_zero_vector(int);
double **allocate_matrix(int,int);
double maxval_vec(double *, int);
void free_matrix(double **, int);
double *Gauss(double **, double *, int, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    int i,j, B=1;
    clock_t start, end;

/*
    Values of 2^n for easy copying during testing
    2^30 = 1073741824
    2^29 = 536870912
    2^28 = 268435456
    2^27 = 134217728
    2^26 = 67108864
    2^25 = 33554432
    2^24 = 16777216
    2^23 = 8388608
    2^20 = 1048576
*/
    int N = 32;
    double delta = 1.0/((double)N);
    printf("%g\n", delta);
    printf("%g\n", delta*delta);

    double *Y = allocate_zero_vector(N-1);
    for (i=1; i<N; i++){
        /*if ( (double)i/N == 0.5 || (double)i/N == 0.25){
            Y[i] = -40.0;
        }else */if ((double)i/N <= 0.5 && (double)i/N > 0.25){
            Y[i] = -80.0;
        } else{Y[i] = 0.0;}
        Y[i] *= delta;
    }

    double **A_banded = allocate_matrix(N+1,2*B+1);

    for (i=1; i<=N-1; i++){ //print to see what it is
        for (j=1;j<2*(B+1);j++){
            A_banded[i][j]=0.0;
        }
    }

    for (i=1; i<=N-1; i++){
        A_banded[i][B+1] = -2.0;
        A_banded[i][B+2] = A_banded[i][B] = 1.0;
    }

    start = clock();
    //mprintf("MAXVAL(Y): %g\n", maxval_vec(Y,N-1));
    double * x = BGauss(A_banded,Y,N-1,B);
    free_matrix(A_banded, N-1);
    free(Y);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    double max_value = maxval_vec(x, N-1);
    printf("\nMax Value is: %g\n", max_value);
    printf("Time taken: %f\n", time_taken);


    for (i=1; i<N; i++){
                x[i] *= delta;
    }
    /*printf("The returned vector is\n");
    print_vector(x,N-1);*/

    //double max_value = maxval_vec(x, N-1);
    printf("\nMax Value is: %g\n", max_value*delta);
}
