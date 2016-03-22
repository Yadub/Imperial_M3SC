#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

double *solve_1d_gauss(int, bool);
double *solve_1d_bgauss(int, bool);
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
double **make_AGauss1D(int);
double **make_ABGauss1D(int, int);
double *make_Yvec1D(int, bool, double);
void print_vector(double *, int);
void print_matrix(double **, int, int);
void multiply_vec(double *, int, double);
int maxvalpos_vec(double *, int);
void free_matrix(double **, int);
double *Gauss(double **, double *, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    /* Yadu Bhageria, 00733164, M3SC */
    int i,N;
    print_statements();
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


    printf("            |                  GAUSS                           |     BGAUSS\n");
    printf("           N|    maxval,   maxval pos,    cpu time,   wall time|    maxval,   maxval pos,    cpu time,   wall time|");

    int maxgauss = 16;

    for (i=3; i<=maxgauss; i++){
        N = pow(2,i);
        printf("\n%12d|", N);
        solve_1d_gauss(N,false);
        solve_1d_bgauss(N,true);
    }
    for (i=maxgauss+1; i<28; i++){
        N = pow(2,i);
        printf("\n%12d|", N);
        solve_1d_bgauss(N,false);
        solve_1d_bgauss(N,true);
    }

    printf("\n");
}
/* --------------------------------------------------------------------------- */

double *solve_1d_bgauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    int B=1;
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);

    double *Y = make_Yvec1D(N,smooth,delta);
    double ** A_banded = make_ABGauss1D(N,B);

    start = clock();
    gettimeofday(&wt_start,NULL);
    double * x = BGauss(A_banded,Y,N-1,B);
    end = clock();
    gettimeofday(&wt_end,NULL);

    free_matrix(A_banded, N-1);
    free(Y);

    double timetaken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);

    int count = x[0];
    int maxval_position = maxvalpos_vec(x, N-1);
    //multiply_vec(x,N-1,delta);

    double output[]= { x[maxval_position]*delta, maxval_position, timetaken, wt_timetaken};
    return output;
}
/* --------------------------------------------------------------------------- */

void solve_1d_gauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);

    double *Y = make_Yvec1D(N,smooth,delta);
    double ** A = make_AGauss1D(N);

    start = clock();
    gettimeofday(&wt_start,NULL);
    double *x = Gauss(A,Y,N-1);
    end = clock();
    gettimeofday(&wt_end,NULL);

    free_matrix(A, N-1);
    free(Y);

    int count = x[0];
    double timetaken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);
    int maxval_position = maxvalpos_vec(x, N-1);
    //multiply_vec(x,N,delta);

    printf("%10.6f, %12d, %11.8f, %11.8f|", x[maxval_position]*delta, maxval_position, timetaken, wt_timetaken);

}
/* --------------------------------------------------------------------------- */
