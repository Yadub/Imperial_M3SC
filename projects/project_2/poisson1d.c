#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

void solve_1d_gauss(int, bool);
void solve_1d_bgauss(int, bool);
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_zero_vector(int);
double **allocate_matrix(int,int);
int maxvalpos_vec(double *, int);
void free_matrix(double **, int);
double *Gauss(double **, double *, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    /* Yadu Bhageria, 00733164, M3SC */
    int i,i1,i2,N,gauss;
/*
    Values of 2^n
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

    printf("Enter 0 for Gauss and anything else for BGuasss: ");
    scanf("%d",&gauss);
    printf("\nEnter range of exponents of 2 to run for (i1 i2): ");
    scanf("%d %d", &i1, &i2);


    printf("\nSolving using %s function\n", gauss==0 ? "Gauss" : "BGauss");
    printf("\n           N,     maxval,     maxval x,  time taken,   smooth?\n");
    for (i=i1; i<=i2; i++){
        N = pow(2,i);
        if (gauss == 0){
            solve_1d_gauss(N,false);
            solve_1d_gauss(N,true);
        } else{
            solve_1d_bgauss(N,false);
            solve_1d_bgauss(N,true);
        }

    }


}
/* --------------------------------------------------------------------------- */

void solve_1d_bgauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    int i, B=1;
    clock_t start, end;

    double delta = 1.0/((double)N);
    // printf("%g\n", delta);
    // printf("%g\n", delta*delta);

    double *Y = allocate_zero_vector(N-1);
    for (i=1; i<N; i++){
        if ( (double)i/N == 0.5 || (double)i/N == 0.25){
            if (smooth == true){
                Y[i] = -40.0;
            } else{
            Y[i] = -80.0;
            }
        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
            Y[i] = -80.0;
        } else{Y[i] = 0.0;}
        Y[i] *= delta;
    }

    double **A_banded = allocate_matrix(N-1,2*B+1);

    for (i=1; i<=N-1; i++){
        A_banded[i][B+1] = -2.0;
        A_banded[i][B+2] = A_banded[i][B] = 1.0;
    }

    start = clock();
    double * x = BGauss(A_banded,Y,N-1,B);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    free_matrix(A_banded, N-1);

    free(Y);

    int maxval_position = maxvalpos_vec(x, N-1);

    for (i=1; i<N; i++){
                x[i] *= delta;
    }

    printf("%12d, %10.6f, %12d, %11.8f,   %s\n", N, x[maxval_position], maxval_position, time_taken, smooth ? "true": "false");

}
/* --------------------------------------------------------------------------- */

void solve_1d_gauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    int i;
    clock_t start, end;

    double delta = 1.0/((double)N);
    // printf("%g\n", delta);
    // printf("%g\n", delta*delta);

    double *Y = allocate_zero_vector(N-1);
    for (i=1; i<N; i++){
        if ( (double)i/N == 0.5 || (double)i/N == 0.25){
            if (smooth == true){
                Y[i] = -40.0;
            } else{
            Y[i] = -80.0;
            }
        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
            Y[i] = -80.0;
        } else{Y[i] = 0.0;}
        Y[i] *= delta;
    }

    double **A = allocate_matrix(N-1,N-1);

    for (i=1; i<=N-1; i++){
        A[i][i] = -2.0;
        if (i>1){
            A[i][i-1] = 1.0;
        }
        if (i<N-1){
            A[i][i+1] = 1.0;
        }
    }

    start = clock();
    double *x = Gauss(A,Y,N-1);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    free_matrix(A, N-1);
    free(Y);

    int maxval_position = maxvalpos_vec(x, N-1);

    for (i=1; i<N; i++){
                x[i] *= delta;
    }

    printf("%12d, %10.6f, %12d, %11.8f,   %s\n", N, x[maxval_position], maxval_position, time_taken, smooth ? "true": "false");

}
