#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <omp.h>
/*incase Pi is not defined */
#ifndef M_PI
#   define M_PI acos(-1.)
#endif
/* --Data-structure-for-moving-wanted-data-between-functions------------------ */
typedef struct poisson2d_data {
    double maxval;
    double xpos;
    double ypos;
    double cpu_time;
    double wall_time;
} poisson2d_data;
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
double *allocate_zero_vector(int);
double *SFactors(int);
double *make_Yvec2D(int, bool, double);
int FastSN(double *, double *, double *, double *,int, int);
int maxvalpos_vec(double *, int);
void contour_print(double *, int);
/* -Functions-implemented-in-current-file------------------------------------- */
double *cos_vec(int);
poisson2d_data sn_poisson2d(int, bool);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N, i, j;
    poisson2d_data Phi_FD, Phi_a;
    print_statements();
    printf("Pow of 2|      N     | FD  Maxval |    x pos   |    y pos   |  A Maxval  |    x pos   |    y pos   |  CPU Time  |  Wall Time |\n");
    printf("--------|------------|------------|------------|------------|------------|------------|------------|------------|------------|\n");
    int N1[] = {5,6,8};

    for (i=0; i<=15; i++){
        for (j=0; j<3; j++){
            //Solve Poisson 2D for the exact and non exact cases
            N = (int) N1[j]*pow(2,i);
            Phi_a = sn_poisson2d(N, true);
            Phi_FD = sn_poisson2d(N, false);
            //Print out acquired data
            printf(" %1d*2^%2d |%11d |",N1[j]/(int)pow(2,j), i+j, N);
            printf(" %10.6f | %10.6f | %10.6f |", Phi_FD.maxval, Phi_FD.xpos, Phi_FD.ypos);
            printf(" %10.6f | %10.6f | %10.6f | %10.6f | %10.6f |\n", Phi_a.maxval, Phi_a.xpos, Phi_a.ypos, Phi_a.cpu_time, Phi_a.wall_time);
        }
    }
}
/* --------------------------------------------------------------------------- */
double *cos_vec(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *C = allocate_zero_vector(N);
    for (int i=0; i<=N; i++){
        C[i] = cos(i*M_PI/N);
    }
    return C;
}
/* --------------------------------------------------------------------------- */
poisson2d_data sn_poisson2d(int N, bool analytic){
    /* Yadu Bhageria, 00733164, M3SC */
    int i, j, rv, returnval = 0;
    clock_t start, end;
    struct timeval walltime_s, walltime_e;
    poisson2d_data data;

    //Initialize Variables and Memory for Data
    double delta = 1./N;
    int grid_size = (N-1)*(N-1);
    double *S = SFactors(N);
    double *x = allocate_zero_vector(grid_size);
    double *w = allocate_zero_vector(grid_size);
    double *y = make_Yvec2D(N,true,-1.);
    double *C = cos_vec(N);

    //Start Timing
    start = clock();
    gettimeofday(&walltime_s,NULL);

    //Transform along rows of the grid
    #pragma omp parallel for
    for (i=0; i<N-1; i++){
        rv = FastSN(x-i, y-i, w-i, S, N, N-1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Transform along columns of the grid
    #pragma omp parallel for
    for (j=0; j<N-1; j++){
        rv = FastSN(y+j*(N-1), x+j*(N-1), w+j*(N-1), S, N, 1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Compute Phi based whether Analytic or FD
    if (analytic){
        double constant = 4. / (N*N * M_PI*M_PI);
        #pragma omp parallel for
        for (i=1; i<N; i++){
            for (j=1; j<N; j++){
                x[(N-1)*(i-1)+j] =  constant * y[(N-1)*(i-1)+j] / (i*i + j*j);
            }
        }
    } else {
        double constant = 4. / (N*N);
        #pragma omp parallel for
        for (i=1; i<N; i++){
            for (j=1; j<N; j++){
                x[(N-1)*(i-1)+j] =  delta*delta * constant * y[(N-1)*(i-1)+j] / (4. - 2.*C[i] - 2.*C[j]);
            }
        }
    }
    //Transform back along columns of the grid
    #pragma omp parallel for
    for (j=0; j<N-1; j++){
        rv = FastSN(y+j*(N-1), x+j*(N-1), w+j*(N-1), S, N, 1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Transform back along rows of the grid
    #pragma omp parallel for
    for (i=0; i<N-1; i++){
        rv = FastSN(x-i, y-i, w-i, S, N, N-1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Finish timing
    end = clock();
    gettimeofday(&walltime_e,NULL);

    //Compute the maxval, its position and time taken
    int maxvalpos = maxvalpos_vec(x,grid_size);
    int maxval_ypos = maxvalpos % (N-1);
    int maxval_xpos = 1 + (maxvalpos-maxval_ypos)/(N-1);
    data.maxval = x[maxvalpos];
    data.ypos = (double) maxval_ypos / N;
    data.xpos = (double) maxval_xpos / N;
    data.cpu_time = ((double)end-start)/CLOCKS_PER_SEC;
    data.wall_time = (double)(walltime_e.tv_sec - walltime_s.tv_sec + (walltime_e.tv_usec - walltime_s.tv_usec)/1000000.0);

    /*
    // To print out the contour plot
    if (N>=64) contour_print(x,N);
    */

    //Free Memory
    free(x);free(y);free(w);free(S);

#ifdef DEBUG
    printf("DEBUG REPORT| RV = %d\n", returnval);
#endif

    return data;
}
/* --------------------------------------------------------------------------- */
