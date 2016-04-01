#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* -Functions-needed-from-other-files----------------------------------------- */
void print_vector(double *, int);
double *SFactors(int);
double *allocate_zero_vector(int);
double *SFactors(int);
double **Sn_matrix(int);
double **Un_matrix(int);
double **Tn_matrix(int);
double **Tnt_matrix(int);
void multiply_vec(double *, int, double);
double * multiply_matrix_vector(double **, double *, int);
void print_matrix(double **, int, int);
void print_vector(double *, int);
int FastSN(double *, double *, double *, double *,int, int);
int FastTN(double *, double *, double *, double *,int, int);
int FastUN(double *, double *, double *, double *,int, int);
/* --------------------------------------------------------------------------- */
int main(void){
    int N;

    printf("Enter N: ");
    scanf("%d", &N);
    printf("\n");

    printf("Testing Sn\n");
    double *xp = allocate_zero_vector(N-1);
    for (int i=1; i<N; i++){
        xp[i] = (double)i;
    }

    double **Sn = Sn_matrix(N);
    double *y = multiply_matrix_vector(Sn,xp,N-1);
    multiply_vec(y,N-1,2./N);

    print_vector(multiply_matrix_vector(Sn,y,N-1),N-1);

    double *S = SFactors(N);
    double *x = allocate_zero_vector(N-1);
    double *w = allocate_zero_vector(N-1);
    int returnval = FastSN(x,y,w,S,N,1);
    printf("Returned Value: %d\n", returnval);
    print_vector(x,N-1);

}
/* --------------------------------------------------------------------------- */
