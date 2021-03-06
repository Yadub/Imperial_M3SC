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
double **Un_matrix(int);
double **Tn_matrix(int);
double **Tnt_matrix(int);
double * multiply_matrix_vector(double **, double *, int);
double * add_vectors(double *, double *, double, int);
void print_matrix(double **, int, int);
void print_vector(double *, int);
int FastSN(double *, double *, double *, double *,int, int);
int FastTN(double *, double *, double *, double *,int, int);
int FastUN(double *, double *, double *, double *,int, int);
/* --------------------------------------------------------------------------- */
int main(void){
    /* Yadu Bhageria, 00733164, M3SC */
    int N,STU;

    print_statements();

    printf("Enter 1,2,3 for Sn,Tn,Un: ");
    scanf("%d", &STU);
    printf("\n");

    if (STU!=1 && STU!=2 && STU!=3){
        printf("Incorrect number entered. Terminating.\n");
    }  else{
        printf("Enter N: ");
        scanf("%d", &N);
        printf("\n");

        double *y = allocate_zero_vector(N);
        for (int i=1; i<=N; i++){
            y[i] = (double)i;
        }
        switch (STU) {
            case 1:{
                printf("Testing Sn\n");
                double **Sn = Sn_matrix(N);
                print_vector(multiply_matrix_vector(Sn,y,N-1),N-1);

                double *S = SFactors(N);
                double *x = allocate_zero_vector(N-1);
                double *w = allocate_zero_vector(N-1);
                int returnval = FastSN(x,y,w,S,N,1);
                printf("Returned Value: %d\n", returnval);
                print_vector(x,N-1);
                print_vector(add_vectors(x,multiply_matrix_vector(Sn,y,N-1),-1.,N-1),N-1);
                break;
            }
            case 2:{
                printf("Testing Tn\n");
                double **Tn = Tn_matrix(N);
                double *A = multiply_matrix_vector(Tn,y,N);
                print_vector(A,N);

                double *S = SFactors(N);
                double *x = allocate_zero_vector(N);
                double *w = allocate_zero_vector(N);
                int returnval = FastTN(x,y,w,S,N,1);
                printf("Returned Value: %d\n", returnval);
                print_vector(x,N);
                print_vector(add_vectors(x,A,-1.,N),N);
                break;
            }
            case 3:{
                printf("Testing Un\n");
                double **Un = Un_matrix(N);
                double *A = multiply_matrix_vector(Un,y,N);
                print_vector(A,N);

                double *S = SFactors(N);
                double *x = allocate_zero_vector(N);
                double *w = allocate_zero_vector(N);
                int returnval = FastUN(x,y,w,S,N,1);
                printf("Returned Value: %d\n", returnval);
                print_vector(x,N);
                print_vector(add_vectors(x,A,-1.,N),N);
                break;
            }
        }
    }
}
/* --------------------------------------------------------------------------- */
