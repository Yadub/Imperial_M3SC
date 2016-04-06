#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
/*incase Pi is not defined */
#ifndef M_PI
#    define M_PI acos(-1.);
#endif
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
void print_vector(double *, int);
double *SFactors(int);
double *allocate_zero_vector(int);
double *SFactors(int);
double **Sn_matrix(int);
double *make_Yvec2D(int, bool, double);
void multiply_vec(double *, int, double);
double * multiply_matrix_vector(double **, double *, int);
void print_vector(double *, int);
void free_matrix(double **, int);
int FastSN(double *, double *, double *, double *,int, int);
int maxvalpos_vec(double *, int);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N1, i;
    double timetaken=0.;
    clock_t start, end;
    print_statements();

    printf("Choose N (2, 3 or 5): ");
    scanf("%d", &N1);
    printf("\n");

    if (N1==2 || N1==3 || N1==5){
        printf(" i |      N     |    Maxval  |    x pos   |    y pos   | Time Taken | RV |\n");
        printf("---|------------|------------|------------|------------|------------|----|\n");

        for (i=3; i<=15; i++){
            int rv, j, k, returnval = 0;
            int N = (int) N1*pow(2,i);
            int grid_size = (N-1)*(N-1);
            double *rho = make_Yvec2D(N,true,1.);

            double *S = SFactors(N);
            double *phi = allocate_zero_vector(grid_size);
            double *w = allocate_zero_vector(grid_size);

            start = clock();

            for (j=0; j<N-1; j++){
                rv = FastSN(phi+j*(N-1),rho+j*(N-1),w+j*(N-1),S,N,1);
                returnval = (rv==-1 || returnval==-1) ? -1 : 0;
            }
            //printf("X transforms done\n");
            for (j=0; j<N-1; j++){
                rv = FastSN(phi-j,rho-j,w-j,S,N,N-1);
                returnval = (rv==-1 || returnval==-1) ? -1 : 0;
            }
            //printf("Y transforms done\n");
            for (j=1; j<N; j++){
                for (k=1; k<N; k++){
                    phi[(N-1)*(j-1)+k] = 4.*phi[(N-1)*(j-1)+k]/N/N;
                    phi[(N-1)*(j-1)+k] = phi[(N-1)*(j-1)+k]/(M_PI*M_PI*(k*k+j*j));
                }
            }
            //printf("Phi calculation done\n");
            for (j=0; j<N-1; j++){
                rv = FastSN(rho+j*(N-1),phi+j*(N-1),w+j*(N-1),S,N,1);
                returnval = (rv==-1 || returnval==-1) ? -1 : 0;
            }
            //printf("PhiX transforms done\n");
            for (j=0; j<N-1; j++){
                rv = FastSN(rho-j,phi-j,w-j,S,N,N-1);
                returnval = (rv==-1 || returnval==-1) ? -1 : 0;
            }
            //printf("PhiY transforms done\n");

            end = clock();

            int maxvalpos = maxvalpos_vec(rho,grid_size);
            int maxval_ypos = maxvalpos % (N-1);
            int maxval_xpos = 1 + (maxvalpos-maxval_ypos)/(N-1);
            timetaken = ((double)end-start)/CLOCKS_PER_SEC;

            //printf("%d, %d, %d, %f\n\n", maxvalpos, maxval_xpos, maxval_ypos,rho[maxvalpos]);
            printf("%3d|%12d| %10.6f | %10.6f | %10.6f | %10.6f | %2d |\n", i+1, N, rho[maxvalpos], (double)maxval_xpos/N,(double)maxval_ypos/N, timetaken, returnval);

            free(phi);free(rho);free(w);free(S);
        }
    } else {
        printf("Please enter a valid value for N\n");
    }
}
/* --------------------------------------------------------------------------- */
