#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/* Yadu Bhageria, 00733164, M3SC */

/* -Functions-needed-from-other-files----------------------------------------- */
void print_statements();
void print_vector(double *, int);
void print_matrix(double **, int, int);
double *allocate_zero_vector(int);
void free_matrix(double **);
/* -Functions-implemented-in-current-file------------------------------------- */
double *Gauss(double **, double *, int);
/* --------------------------------------------------------------------------- */

double *Gauss(double **A, double *y, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j, singular = 0;
    unsigned long long int count = 0;
    double *x = allocate_zero_vector(N);
#ifdef DEBUG
    printf("\nDEBUG REPORT| Inputted Values (A and y)\n");
    print_vector(y,N);
    print_matrix(A,N,N);
#endif
/*
    Decompose A along with y
*/
#pragma omp parallel private(i)
{
    for (i=1; i<N && singular!=1; i++){
        if (A[i][i]==0){
            printf("ERROR| Zero on the diagonal of the matrix during Guassian Elimiation. Considering it as singular, exitting Guass(), and returning a zero vector\n");
            singular = 1;
        }
        #pragma omp for reduction(+:count)
        for (j=i+1; j<N+1; j++){
            if (A[j][i]!=0)
            {
                double ratio = A[j][i]/A[i][i];
                for (int k=1+i; k<N+1; k++){
                    A[j][k] -= ratio*A[i][k];
                    count += 2;
                }
                y[j] -= ratio*y[i];
                count += 3;
            }
        }
    }
}
/* Check if the matrix was considered singular and if so then return 0 */
    if (singular==1){
        return x;
    }
/*
    Substitute back in to get x
*/
#ifdef DEBUG
    printf("DEBUG REPORT| Converted Values (A and y)\n" );
    print_matrix(A,N,N);
    print_vector(y,N);
    printf("DEBUG REPORT| Reduction count = %d\n", count);
#endif
    x[N] = y[N]/A[N][N];
    count++;
    for (i=N-1; i>0; i--){
        x[i] += y[i];
        for (j=N; j>i; j--){
            x[i] -= A[i][j]*x[j];
            count += 2;
        }
        x[i] /= A[i][i];
        count +=2;
    }
    x[0] = (double) count;

    return x;
}
