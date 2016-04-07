#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
/*incase Pi is not defined */
#ifndef M_PI
#   define M_PI acos(-1.);
#endif
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
double *allocate_zero_vector(int);
double *SFactors(int);
double *make_Yvec2D(int, bool, double);
int FastSN(double *, double *, double *, double *,int, int);
int maxvalpos_vec(double *, int);
/* --------------------------------------------------------------------------- */
int sn_poisson2d(int);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N1, i;

    print_statements();

    printf("Choose N (2, 3 or 5): ");
    scanf("%d", &N1);
    printf("\n");

    if (N1==2 || N1==3 || N1==5){
        printf(" i |      N     |    Maxval  |    x pos   |    y pos   | Time Taken | RV |\n");
        printf("---|------------|------------|------------|------------|------------|----|\n");

        for (i=3; i<=11; i++){
            int N = (int) N1*pow(2,i);
            printf("%3d|", i+1);
            sn_poisson2d(N);
        }
    } else {
        printf("Please enter a valid value for N\n");
    }
}
/* --------------------------------------------------------------------------- */
int sn_poisson2d(int N){
    int i, j, rv, returnval = 0;
    clock_t start, end;
    //Initialize Memory
    int grid_size = (N-1)*(N-1);
    double *S = SFactors(4*N);
    double *x = allocate_zero_vector(grid_size);
    double *w = allocate_zero_vector(grid_size);
    double *y = make_Yvec2D(N,true,1.);

    //Start Timing
    start = clock();

    //Transform along rows of the grid
    for (i=0; i<N-1; i++){
        rv = FastSN(x-i, y-i, w-i, S, N, N-1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Transform along columns of the grid
    for (j=0; j<N-1; j++){
        rv = FastSN(y+j*(N-1), x+j*(N-1), w+j*(N-1), S, N, 1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Compute Phi
    double constant = 4. / (N*N * M_PI*M_PI);
    for (i=1; i<N; i++){
        for (j=1; j<N; j++){
            x[(N-1)*(i-1)+j] =  constant * y[(N-1)*(i-1)+j] / (i*i + j*j);
        }
    }
    //Transform back along columns of the grid
    for (j=0; j<N-1; j++){
        rv = FastSN(y+j*(N-1), x+j*(N-1), w+j*(N-1), S, N, 1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Transform back along rows of the grid
    for (i=0; i<N-1; i++){
        rv = FastSN(x-i, y-i, w-i, S, N, N-1);
        returnval = (rv==-1 || returnval==-1) ? -1 : 0;
    }
    //Finish timing
    end = clock();

    //Compute the maxval, its position and time taken
    int maxvalpos = maxvalpos_vec(x,grid_size);
    int maxval_ypos = maxvalpos % (N-1);
    int maxval_xpos = 1 + (maxvalpos-maxval_ypos)/(N-1);
    double timetaken = ((double)end-start)/CLOCKS_PER_SEC;

    //Print out the needed Data
    printf("%12d| %10.6f | %10.6f | %10.6f | %10.6f | %2d |\n", N, x[maxvalpos], (double)maxval_xpos/N,(double)maxval_ypos/N, timetaken, returnval);

    //Free memory
    free(x);free(y);free(w);free(S);

    return returnval;
}
