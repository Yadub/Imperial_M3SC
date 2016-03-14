#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void print_matrix(double **A, int N, int M){
    /* Yadu Bhageria, 00733164, M3SC */
/*
    Extremely useful for debugging
*/
    for(int i=1; i<N+1; i++){
        for(int j=1; j<M+1; j++){
            printf("%8.5g ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */

void print_vector(double *x, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    for (int i=1; i<N+1; i++){
        printf("%8.5g\n", x[i]);
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */

double **allocate_matrix(int N, int M){
    /* Yadu Bhageria, 00733164, M3SC */
    double ** A;
    A=(double **) malloc((N+1)*sizeof(double *));
    for(int i=1; i<N+1; i++){
        A[i]=(double *) malloc((M+1)*sizeof(double));
    }
    return A;
}
/* --------------------------------------------------------------------------- */

double *allocate_vector(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *X;
    X = (double *) calloc((N+1),sizeof(double));
    return X;
}
/* --------------------------------------------------------------------------- */
