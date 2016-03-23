#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>


double *make_Yvec3D(int, double);
void solve_3d_gauss(int);
void solve_3d_bgauss(int);
void contour_print3D(double *, int);
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

    printf("Enter 0 for Gauss and anything else for BGauss: ");
    scanf("%d",&gauss);

    printf("\nSolving using %s function\n", gauss==0 ? "Gauss" : "BGauss");
    printf("           N|    maxval, maxval pos x, maxval pos y, maxval pos z,    cpu time,   wall time,       speed");
    double n_val[] = {5,6,8,10,12,16,20,24,28,32,36,40,48,64,80,96,128};

    for (i=0; i<17; i++){
        N = n_val[i];
        if (gauss == 0){
            printf("\n%12d|", N);
            solve_3d_gauss(N);
        } else {
            printf("\n%12d|", N);
            solve_3d_bgauss(N);
        }
    }
    printf("\n");
    //solve_3d_bgauss(32);
}
/* --------------------------------------------------------------------------- */
void solve_3d_bgauss(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,k, B=(N-1)*(N-1), grid_size = (N-1)*(N-1);
    int cube_size = (N-1)*grid_size;
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);

    double *F = make_Yvec3D(N,delta*delta);
    double **A_banded = allocate_matrix(cube_size,2*B+1);
    for (k=1; k<N; k++){
        for (i=1; i<N; i++){
            for (j=1; j<N; j++){
                int current_row = grid_size*(k-1)+(N-1)*(i-1)+j;
                A_banded[current_row][B+1] = -6.0;
                A_banded[current_row][1] = 1.0;
                A_banded[current_row][2*B+1] = 1.0;
                if (i!=1){
                    A_banded[current_row][B+1-(N-1)] = 1.0;
                }
                if (i!=(N-1)){
                    A_banded[current_row][B+1+N-1] = 1.0;
                }
                if (j==1){
                    A_banded[current_row][B+2] = 1.0;
                } else if (j==N-1){
                    A_banded[current_row][B] = 1.0;
                } else {
                    A_banded[current_row][B+2] = A_banded[current_row][B] = 1.0;
                }
            }
        }
    }

    start = clock();
    gettimeofday(&wt_start,NULL);
    double * v = BGauss(A_banded,F,cube_size,B);
    end = clock();
    gettimeofday(&wt_end,NULL);
    free_matrix(A_banded, cube_size);
    free(F);

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);

    int maxval_position = maxvalpos_vec(v, cube_size);
    int z_maxval = maxval_position % (N-1);
    int y_maxval = (maxval_position%(N-1)*(N-1)-z_maxval)/(N-1) + 1;
    int x_maxval = (maxval_position-(N-1)*(y_maxval-1)-z_maxval)/(N-1)/(N-1)+ 1;
/*
    printf("\n%d\n", maxval_position);
    printf("\n%d\n", z_maxval);
    printf("\n%d\n", y_maxval);
    printf("\n%d\n", x_maxval);
*/
    //contour_print3D(v,N);

    double speed = 1e-9 * v[0] / wt_timetaken;
    printf("%10.6f, %12.10f, %12.10f, %12.10f, %11.8f, %11.8f, %11.8f|", v[maxval_position], (double)x_maxval/N, (double)y_maxval/N, (double)z_maxval/N, time_taken, wt_timetaken, speed);
    free(v);
}
/* --------------------------------------------------------------------------- */
void solve_3d_gauss(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,k,grid_size = (N-1)*(N-1);
    int cube_size = (N-1)*grid_size;
    clock_t start, end;
    struct timeval wt_start, wt_end;

    double delta = 1.0/((double)N);
    double *F = make_Yvec3D(N,delta*delta);
    double **A = allocate_matrix(cube_size,cube_size);
    for (k=1; k<N; k++){
        for (i=1; i<N; i++){
            for (j=1; j<N; j++){
                int current_row = grid_size*(k-1)+(N-1)*(i-1)+j;
                A[current_row][current_row] = -6.0;
                if (j!=1){
                    A[current_row][current_row-1] = 1.0;
                }
                if (j!=(N-1)){
                    A[current_row][current_row+1] = 1.0;
                }
                if (i!=1){
                    A[current_row][current_row-(N-1)] = 1.0;
                }
                if (i!=(N-1)){
                    A[current_row][current_row+(N-1)] = 1.0;
                }
                if (k!=1){
                    A[current_row][current_row-(N-1)*(N-1)] = 1.0;
                }
                if (k!=N-1){
                    A[current_row][current_row+(N-1)*(N-1)] = 1.0;
                }
            }
        }
    }

    start = clock();
    gettimeofday(&wt_start,NULL);
    double * v = Gauss(A,F,cube_size);
    gettimeofday(&wt_end,NULL);
    end = clock();
    free_matrix(A, cube_size);
    free(F);

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    double wt_timetaken = (double)(wt_end.tv_sec - wt_start.tv_sec + (wt_end.tv_usec - wt_start.tv_usec)/1000000.0);

    int maxval_position = maxvalpos_vec(v, cube_size);
    int z_maxval = maxval_position % (N-1);
    int y_maxval = (maxval_position%(N-1)*(N-1)-z_maxval)/(N-1) + 1;
    int x_maxval = (maxval_position-(N-1)*(y_maxval-1)-z_maxval)/(N-1)/(N-1)+ 1;
/*
    printf("\n%d\n", maxval_position);
    printf("\n%d\n", z_maxval);
    printf("\n%d\n", y_maxval);
    printf("\n%d\n", x_maxval);
*/
    double speed = 1e-9 * v[0] / wt_timetaken;
    printf("%10.6f, %12.10f, %12.10f, %12.10f, %11.8f, %11.8f, %11.8f|", v[maxval_position], (double)x_maxval/N, (double)y_maxval/N, (double)z_maxval/N, time_taken, wt_timetaken, speed);
    free(v);
}
/* --------------------------------------------------------------------------- */
double *make_Yvec3D(int N, double delta){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,k;
    double *F = allocate_zero_vector( (N-1)*(N-1)*(N-1) );
    for (k=1; k<N; k++){
        int current_grid = (N-1)*(N-1)*(k-1);
        if ((double)k/N == 0.5 || (double)k/N == 0.25){
            for (j=1; j<N; j++){
                if ((double)j/N == 0.5 || (double)j/N == 0.25){
                    for (i=1; i<N; i++){
                        if ((double)i/N == 0.5 || (double)i/N == 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -25.0*delta;
                        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -50.0*delta;
                        }
                    }
                } else if ((double)j/N < 0.5 && (double)j/N > 0.25){
                    for (i=1; i<N; i++){
                        if ((double)i/N == 0.5 || (double)i/N == 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -50.0*delta;
                        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -100.0*delta;
                        }
                    }
                }
            }
            /* --- */
        } else if ((double)k/N < 0.5 && (double)k/N > 0.25){
            for (j=1; j<N; j++){
                if ((double)j/N == 0.5 || (double)j/N == 0.25){
                    for (i=1; i<N; i++){
                        if ((double)i/N == 0.5 || (double)i/N == 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -50.0*delta;
                        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -100.0*delta;
                        }
                    }
                } else if ((double)j/N < 0.5 && (double)j/N > 0.25){
                    for (i=1; i<N; i++){
                        if ((double)i/N == 0.5 || (double)i/N == 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -100.0*delta;
                        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                            F[current_grid+(N-1)*(j-1)+i] = -200.0*delta;
                        }
                    }
                }
            }
        }
    }
    return F;
}
/* --------------------------------------------------------------------------- */
void contour_print3D(double *x, int N){
    int i,j;
    for (j=0; j<=32; j++){
        for (i=0; i<=32; i++){
            printf("     0.0,");
        }
        printf("\n");
    }
    for (i=1; i<32; i++){
        contour_print(x + (i-1)*(N-1)*(N-1), N);
        printf("\n");
    }
    printf("\n");
    for (j=0; j<=32; j++){
        for (i=0; i<=32; i++){
            printf("     0.0,");
        }
        printf("\n");
    }
}
