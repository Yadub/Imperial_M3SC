#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
    int N1;
    double timet1=0., timet2;
    clock_t start, end;
    print_statements();

    printf("Choose N (2, 3 or 5): ");
    scanf("%d", &N1);
    printf("\n");

    if (N1==2 || N1==3 || N1==5){
        printf(" i |      N     |  DirectSN  |   FastSN   | RV |\n");
        printf("---|------------|------------|------------|----|\n");

        for (int i=1; i<=30; i++){
            int N = (int) N1*pow(2,i);
            double *xp = allocate_zero_vector(N);
            for (int i=1; i<=N; i++){
                xp[i] = (double)i;
            }

            if (i>100){
                double **Sn = Sn_matrix(N);
                start = clock();
                multiply_matrix_vector(Sn,xp,N-1);
                end = clock();

                free_matrix(Sn,N-1);
                timet1 = ((double)end-start)/CLOCKS_PER_SEC;
            }

            double *S = SFactors(N);
            double *x = allocate_zero_vector(N);
            double *w = allocate_zero_vector(N);

            start = clock();
            int returnval = FastSN(x,xp,w,S,N,1);
            end = clock();
            timet2 = ((double)end-start)/CLOCKS_PER_SEC;

            printf("%3d|%12d| %10.4e | %10.4e | %2d |\n", i+1, N, timet1, timet2, returnval);

            free(x);free(xp);free(w);free(S);
        }
    } else {
        printf("Please enter a valid value for N\n");
    }
}
/* --------------------------------------------------------------------------- */
