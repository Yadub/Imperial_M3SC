#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
void print_vector(double *, int);
double *SFactors(int);
double *allocate_zero_vector(int);
double *SFactors(int);
double **Sn_matrix(int);
void multiply_vec(double *, int, double);
double * multiply_matrix_vector(double **, double *, int);
void print_vector(double *, int);
void free_matrix(double **, int);
int FastSN(double *, double *, double *, double *,int, int);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N;

    print_statements();

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
    free_matrix(Sn,N-1);
    double *S = SFactors(4.*N);
    double *x = allocate_zero_vector(N-1);
    double *w = allocate_zero_vector(N-1);
    int returnval = FastSN(x,y,w,S,N,1);
    printf("Returned Value: %d\n", returnval);
    print_vector(x,N-1);


#ifdef DEBUG
    printf("S[0]=%g, S[1]=%g, S[2]=%g, S[3]=%g, S[4]=%g, S[5]=%g\n", S[0],S[1],S[2],S[3],S[4],S[5]);
#endif
}
/* --------------------------------------------------------------------------- */
