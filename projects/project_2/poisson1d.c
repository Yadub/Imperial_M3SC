#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

void solve_1d_gauss(int, bool);
void solve_1d_bgauss(int, bool);
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
    int i,i1,i2,N,gauss;
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

    printf("Enter 0 for Gauss and anything else for BGuasss: ");
    scanf("%d",&gauss);
    printf("\nEnter range of exponents of 2 to run for (i1 i2): ");
    scanf("%d %d", &i1, &i2);


    printf("\nSolving using %s function\n", gauss==0 ? "Gauss" : "BGauss");
    printf("            |                  ROUGH                           |     SMOOTH\n");
    printf("           N|    maxval,   maxval pos,    cpu time,   wall time,       speed|    maxval,   maxval pos,    cpu time,   wall time,       speed|");
    for (i=i1; i<=i2; i++){
        N = pow(2,i);
        if (gauss == 0){
            printf("\n%12d|", N);
            solve_1d_gauss(N,false);
            solve_1d_gauss(N,true);
        } else{
            printf("\n%12d,", N);
            solve_1d_bgauss(N,false);
            solve_1d_bgauss(N,true);
        }

    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */

void solve_1d_bgauss(int N, bool smooth){
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

    int maxval_position = maxvalpos_vec(x, N-1);
    //multiply_vec(x,N-1,delta);
    double speed = 1e-9 * x[0] / wt_timetaken;
    
    printf("%10.6f, %12.10f, %11.8f, %11.8f, %11.8f|", x[maxval_position]*delta, (double)maxval_position/N, timetaken, wt_timetaken, speed);

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

    double timetaken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);
    int maxval_position = maxvalpos_vec(x, N-1);
    //multiply_vec(x,N,delta);

    double speed = 1e-9 * x[0] / wt_timetaken;

    printf("%10.6f, %12.10f, %11.8f, %11.8f, %11.8f|", x[maxval_position]*delta, (double)maxval_position/N, timetaken, wt_timetaken, speed);

}
/* --------------------------------------------------------------------------- */
