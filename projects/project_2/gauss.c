#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Yadu Bhageria, 00733164, M3SC */

/* -Functions-needed-from-other-files----------------------------------------- */

/* -Functions-implemented-in-current-file------------------------------------- */
void print_statements();
void print_vector(double *, int);
void print_matrix(double **, int);
double *Gauss(double **, double *, int);
/* --------------------------------------------------------------------------- */

double *Gauss(double **A, double *y, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j,k;
    double ratio;
    double * x = y;
    //double * y_temp = y;
    //double ** A_temp = A;
#ifdef DEBUG
    print_vector(y,N);
    print_matrix(A,N);
#endif
/*
    Decompose A
*/
    for (i=1; i<N; i++){
        ratio = A[i][i];
        if (ratio!=1.0){
            for (j=i; j<N+1; j++){
                A[i][j] /= ratio;
            }
            y[i] /= ratio;
        }
        printf("Division Over\n");
        print_matrix(A,N);
        print_vector(y,N);
        for (j=i+1; j<N+1; j++){
            if (A[j][i]!=0){
                ratio = A[j][i]/A[i][i];
                for (k=1; k<N+1; k++){
                    A[j][k] -= ratio*A[i][k];
                }
                y[j] -= ratio*y[i];
            }
        }
        printf("Substraction over\n");
        print_matrix(A,N);
        print_vector(y,N);
    }
#ifdef DEBUG
    print_matrix(A,N);
    print_vector(y,N);
#endif
/*
    Substitute back in
*/
double sum;
    x[N] = y[N]/A[N][N];
    for (i=N-1; i>0; i--){
        sum = 0.0;
        sum += y[i];
        for (j=N; j>i; j--){
            sum -= A[i][j]*x[j];
        }
        x[i] = sum/A[i][i];
    }
    return(x);
}
/* --------------------------------------------------------------------------- */

void print_statements(){
    /* Bhageria, Yadu, 00733164, M3SC */
    printf(  "         Name: Bhageria, Yadu");
    printf("\n          CID: 00733164");
	printf("\n  Course Code: 00733164, M3SC");
    printf("\nEmail Address: yrb13@ic.ac.uk");
    printf("\n         Time: %s ",__TIME__);
    printf("\n         Date: %s ",__DATE__);
    printf("\n \n");
}
/* --------------------------------------------------------------------------- */

void print_matrix(double **A, int N){
    /* Yadu Bhageria, 00733164, M3SC */
/*
    Extremely useful for debugging
*/
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N+1; j++){
            printf("%5.3g ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */

void print_vector(double *x, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    for (int i=1; i<N+1; i++){
        printf("%5.3g\n", x[i]);
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */

double **allocate_matrix(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double ** A;
    A=(double **) malloc(N*sizeof(double *));
    for(int i=1; i<N+1; i++){
        A[i]=(double *) malloc(2*N*sizeof(double));
    }
    return A;
}
/* --------------------------------------------------------------------------- */

double *allocate_vector(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *X;
    X = (double *) malloc(N*sizeof(double));
    return X;
}
