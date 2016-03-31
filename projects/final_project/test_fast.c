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
double * multiply_matrix_vector(double **, double *, int);
void print_matrix(double **, int, int);
void print_vector(double *, int);
int FastSN(double *, double *, double *, double *,int, int);
/* --------------------------------------------------------------------------- */
int main(void){
    int N;

    printf("Enter N: ");
    scanf("%d", &N);
    printf("\n");

    double *y = allocate_zero_vector(N-1);
    for (int i=1; i<N; i++){
        y[i] = (double)i;
    }

    double **Sn = Sn_matrix(N);
    print_vector(multiply_matrix_vector(Sn,y,N-1),N-1);

    double *S = SFactors(N);
    double *x = allocate_zero_vector(N);
    double *w = allocate_zero_vector(N);
    printf("Test\n" );
    FastSN(x,y,w,S,N,1);
    print_vector(x,N-1);


}
/* --------------------------------------------------------------------------- */
