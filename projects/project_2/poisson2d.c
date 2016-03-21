#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

void solve_2d_gauss(int, bool);
void solve_2d_bgauss(int, bool);
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_2dvector(double *, int, int);
void print_matrix(double **, int, int);
double *allocate_zero_vector(int);
double **allocate_matrix(int,int);
int maxvalpos_vec(double *, int);
void free_matrix(double **, int);
double *Gauss(double **, double *, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
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
    printf("Enter range of exponents of 2 to run for (i1 i2): ");
    scanf("%d %d", &i1, &i2);

    printf("\n           N,     maxval,     maxval x,     maxval y,  time taken,   smooth?\n");
    for (i=i1; i<=i2; i++){
        N = pow(2,i);
        if (gauss == 0){
            solve_2d_gauss(N,false);
            solve_2d_gauss(N,true);
        } else {
            solve_2d_bgauss(N,false);
            solve_2d_bgauss(N,true);
        }
    }
}
/* --------------------------------------------------------------------------- */
void solve_2d_bgauss(int N, bool smooth){
    int i,j, B=N-1, grid_size = (N-1)*(N-1);
    clock_t start, end;

    double delta = 1.0/((double)N);

    double *F = allocate_zero_vector( (N-1)*(N-1) );

/* Making Y vec for rough */
/*
    for (j=1; j<N; j++){
        if ((double)j/N <= 0.5 && (double)j/N >= 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                }
            }
        }
    }
*/

    for (j=1; j<N; j++){
        if ((double)j/N == 0.5 || (double)j/N == 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -25.0*delta*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                }
            }
        } else if ((double)j/N < 0.5 && (double)j/N > 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta*delta;
                    } else {
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                }
            }
        }
    }

    double **A_banded = allocate_matrix(grid_size,2*B+1);

    for (i=1; i<N; i++){
        for (j=1; j<N; j++){
            A_banded[(N-1)*(i-1)+j][B+1] = -4.0;
            A_banded[(N-1)*(i-1)+j][1] = 1.0;
            A_banded[(N-1)*(i-1)+j][2*B+1] = 1.0;
            if (j==1){
                A_banded[(N-1)*(i-1)+j][B+2] = 1.0;
            } else if (j==N-1){
                A_banded[(N-1)*(i-1)+j][B] = 1.0;
            } else {
                A_banded[(N-1)*(i-1)+j][B+2] = A_banded[(N-1)*(i-1)+j][B] = 1.0;
            }
        }
    }
    //print_vector(F,grid_size);
    //print_matrix(A_banded,grid_size,2*B+1);

    start = clock();
    time_t start_time = time(NULL);
    double * v = BGauss(A_banded,F,grid_size,B);
    time_t end_time = time(NULL);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wall_time = (double)(end_time - start_time);
    free_matrix(A_banded, grid_size);
    free(F);


    int maxval_position = maxvalpos_vec(v, grid_size);
    int y_maxval = maxval_position % (N-1);
    int x_maxval = (maxval_position-y_maxval)/(N-1) + 1;
    //print_2dvector(v,N-1,N-1);
    printf("%12d, %10.6f, %12.9g, %12.9g, %11.8f, %8s, %8.3f\n", N, v[maxval_position],(double)x_maxval/N, (double)y_maxval/N, time_taken, smooth ? "true": "false", wall_time);
}

/* --------------------------------------------------------------------------- */
void solve_2d_gauss(int N, bool smooth){
    int i,j,grid_size = (N-1)*(N-1);
    clock_t start, end;

    double delta = 1.0/((double)N);

    double *F = allocate_zero_vector( (N-1)*(N-1) );

    for (j=1; j<N; j++){
        if ((double)j/N == 0.5 || (double)j/N == 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -25.0*delta*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                }
            }
        } else if ((double)j/N < 0.5 && (double)j/N > 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta*delta;
                    } else {
                        F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    F[(N-1)*(j-1)+i] = -100.0*delta*delta;
                }
            }
        }
    }

    double **A = allocate_matrix(grid_size,grid_size);

    for (i=1; i<N; i++){
        for (j=1; j<N; j++){
            A[(N-1)*(i-1)+j][(N-1)*(i-1)+j] = -4.0;
            if ((N-1)*(i-1)+j < grid_size){
                if (j!=N-1){
                    A[(N-1)*(i-1)+j][(N-1)*(i-1)+j+1] = 1.0;
                }
            }
            if ((N-1)*(i-1)+j > 1){
                if (j!=1){
                    A[(N-1)*(i-1)+j][(N-1)*(i-1)+j-1] = 1.0;
                }
            }
            if ((N-1)*(i-1)+j > N-1){
                A[(N-1)*(i-1)+j][(N-1)*(i-2)+j] = 1.0;
            }
            if ((N-1)*(i-1)+j <= grid_size - (N-1)){
                A[(N-1)*(i-1)+j][(N-1)*(i)+j] = 1.0;
            }
        }
    }
    //print_vector(F,grid_size);
    //print_matrix(A,grid_size,grid_size);
    start = clock();
    time_t start_time = time(NULL);
    double * v = Gauss(A,F,grid_size);
    time_t end_time = time(NULL);
    end = clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wall_time = (double)(end_time - start_time);
    free_matrix(A, grid_size);
    free(F);

    int maxval_position = maxvalpos_vec(v, grid_size);
    int y_maxval = maxval_position % (N-1);
    int x_maxval = (maxval_position-y_maxval)/(N-1) + 1;
    //print_2dvector(v,N-1,N-1);
    printf("%12d, %10.6f, %12.9g, %12.9g, %11.8f, %8s, %6.3f\n", N, v[maxval_position],(double)x_maxval/N, (double)y_maxval/N, time_taken, smooth ? "true": "false", wall_time);
}
