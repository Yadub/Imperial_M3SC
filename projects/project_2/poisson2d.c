#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>


double *make_Yvec2D(int, bool, double);
void solve_2d_gauss(int, bool);
void solve_2d_bgauss(int, bool);
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements(); //contained in the gauss.c file
void print_vector(double *, int);
void print_2dvector(double *, int, int);
void print_matrix(double **, int, int);
void contour_print(double *, int);
double *allocate_zero_vector(int);
double **allocate_matrix(int,int);
int maxvalpos_vec(double *, int);
void free_matrix(double **, int);
double *Gauss(double **, double *, int);
double *BGauss(double **, double *, int, int);
/* --------------------------------------------------------------------------- */

int main(void) {
    /* Yadu Bhageria, 00733164, M3SC */
    int i,N,gauss;
    print_statements();

    printf("Enter 0 for Gauss and anything else for BGauss: ");
    scanf("%d",&gauss);

    printf("\nSolving using %s function\n", gauss==0 ? "Gauss" : "BGauss");
    printf("           N|    maxval, maxval pos x, maxval pos y,    cpu time,   wall time,       speed|    maxval, maxval pos x, maxval pos y,    cpu time,   wall time,       speed|");
    double n_val[] = {8,12,16,20,24,32,40,48,64,80,96};

    for (i=0; i<11; i++){
        N = n_val[i];
        if (gauss == 0){
            printf("\n%12d|", N);
            solve_2d_gauss(N,false);
            solve_2d_gauss(N,true);
        } else {
            printf("\n%12d|", N);
            solve_2d_bgauss(N,false);
            solve_2d_bgauss(N,true);
        }
    }

    for (i=1; i<=15; i++){
        N = 96+32*i;
        if (gauss == 0){
            printf("\n%12d|", N);
            solve_2d_gauss(N,false);
            solve_2d_gauss(N,true);
        } else {
            printf("\n%12d|", N);
            solve_2d_bgauss(N,false);
            solve_2d_bgauss(N,true);
        }
    }
    //solve_2d_bgauss(512,true);
}
/* --------------------------------------------------------------------------- */
void solve_2d_bgauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j, B=N-1, grid_size = (N-1)*(N-1);
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);

    double *F = make_Yvec2D(N,smooth,delta*delta);
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

    start = clock();
    gettimeofday(&wt_start,NULL);
    double * v = BGauss(A_banded,F,grid_size,B);
    end = clock();
    gettimeofday(&wt_end,NULL);
    free_matrix(A_banded, grid_size);
    free(F);

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);

    int maxval_position = maxvalpos_vec(v, grid_size);
    int y_maxval = maxval_position % (N-1);
    int x_maxval = (maxval_position-y_maxval)/(N-1) + 1;

    //contour_print(v,N);

    double speed = 1e-9 * v[0] / wt_timetaken;
    printf("%10.6f, %12.10f, %12.10f, %11.8f, %11.8f, %11.8f|", v[maxval_position], (double)x_maxval/N, (double)y_maxval/N, time_taken, wt_timetaken, speed);
    free(v);
}
/* --------------------------------------------------------------------------- */
void solve_2d_gauss(int N, bool smooth){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,grid_size = (N-1)*(N-1);
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);
    double *F = make_Yvec2D(N,smooth,delta*delta);
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

    start = clock();
    gettimeofday(&wt_start,NULL);
    double * v = Gauss(A,F,grid_size);
    gettimeofday(&wt_end,NULL);
    end = clock();
    free_matrix(A, grid_size);
    free(F);

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);

    int maxval_position = maxvalpos_vec(v, grid_size);
    int y_maxval = maxval_position % (N-1);
    int x_maxval = (maxval_position-y_maxval)/(N-1) + 1;

    double speed = 1e-9 * v[0] / wt_timetaken;
    printf("%10.6f, %12.10f, %12.10f, %11.8f, %11.8f, %11.8f|", v[maxval_position], (double)x_maxval/N, (double)y_maxval/N, time_taken, wt_timetaken, speed);
    free(v);
}
/* --------------------------------------------------------------------------- */
