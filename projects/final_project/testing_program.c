#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
void print_vector(double *, int);
double *SFactors(int);
double **Sn_matrix(int);
double **Un_matrix(int);
double **Tn_matrix(int);
double **Tnt_matrix(int);
double ** multiply_square_matrices(double **, double **, int);
void print_matrix(double **, int, int);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N;

    print_statements();

    printf("Enter N: ");
    scanf("%d", &N);
    printf("\n");
/*
    double * test_factors = SFactors(N);
    print_vector(test_factors, N/2);
*/
/*
    To check Matrix inverses.
*/
/*
    double **A = Sn_matrix(N);
    double **M = multiply_square_matrices(A,A,N-1);
    print_matrix(M,N-1,N-1);
*/
/*
    double **A = Un_matrix(N);
    double **M = multiply_square_matrices(A,A,N);
    print_matrix(M,N,N);
*/
/*
    double **A = Tn_matrix(N);
    double **B = Tnt_matrix(N);
    double **M = multiply_square_matrices(B,A,N);
    print_matrix(M,N,N);
*/
}
/* --------------------------------------------------------------------------- */
