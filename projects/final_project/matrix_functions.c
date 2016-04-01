#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
/*incase Pi is not defined */
#ifndef M_PI
#    define M_PI acos(-1.);
#endif
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
            printf("%6.3g ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */
void print_vector(double *x, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    for (int i=1; i<N+1; i++){
        printf("%3d | %12.6g\n",i, x[i]);
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */
void print_2dvector(double *x, int N, int M){
    /* Yadu Bhageria, 00733164, M3SC */
    for (int j=1; j<M+1; j++){
        for (int i=1; i<N+1; i++){
            printf("%6.3g, ", x[(N)*(i-1)+j]);
        }
        printf("\n");
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */
double **allocate_zero_matrix(int N, int M){
    /* Yadu Bhageria, 00733164, M3SC */

    //The safe approach; better sizes over 2^27 in size
    double ** A;
    A=(double **) malloc((N+1)*sizeof(double *));
    for(int i=1; i<N+1; i++){
        A[i]=(double *) calloc((M+1),sizeof(double));
    }
    return A;
/*
    //The cautious approach:
    double **A; int i;
    A = (double **)malloc((N+1)*sizeof(double *));
    A[0] = (double *)calloc((N*M+1),sizeof(double));
    A[1] = A[0];
    for (i=2; i<=N; i++) A[i] = A[i-1]+M;
    return A;
*/
}
/* --------------------------------------------------------------------------- */
double *allocate_zero_vector(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *X;
    X = (double *) calloc((N+1),sizeof(double));
    return X;
}
/* --------------------------------------------------------------------------- */
int maxvalpos_vec(double * X, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double maxvalue=X[1];
    int xpos = 1;
    for(int i=2; i<N+1; i++){
        if (X[i] > maxvalue){
            maxvalue = X[i];
            xpos = i;
        }
    }
    return xpos;
}
/* --------------------------------------------------------------------------- */
void free_matrix(double **A, int N){
    /* Yadu Bhageria, 00733164, M3SC */

    //for the safe approach
    for (int i=N; i>0; i--) free(A[i]);
/*
    //for the cautious approach
    free(A[0]); free(A);
*/
}
/* --------------------------------------------------------------------------- */
void multiply_vec(double *X, int N, double factor){
    int i;
    for (i=1; i<N+1; i++){
        X[i] *= factor;
    }
}
/* --------------------------------------------------------------------------- */
double *make_Yvec2D(int N, bool smooth, double delta){
    int i,j;
    double *F = allocate_zero_vector( (N-1)*(N-1) );
    for (j=1; j<N; j++){
        if ((double)j/N == 0.5 || (double)j/N == 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -25.0*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta;
                    } else{
                        F[(N-1)*(j-1)+i] = -100.0*delta;
                    }
                }
            }
        } else if ((double)j/N < 0.5 && (double)j/N > 0.25){
            for (i=1; i<N; i++){
                if ((double)i/N == 0.5 || (double)i/N == 0.25){
                    if (smooth == true){
                        F[(N-1)*(j-1)+i] = -50.0*delta;
                    } else {
                        F[(N-1)*(j-1)+i] = -100.0*delta;
                    }
                } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
                    F[(N-1)*(j-1)+i] = -100.0*delta;
                }
            }
        }
    }
    return F;
}
/* --------------------------------------------------------------------------- */
void contour_print(double *x, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    int nby32 = N/32;
    for (i=0; i<=32; i++){
        printf("     0.0,");
    }
    printf("\n");
    for (i=1; i<32; i++){
        printf("     0.0,");
        for (j=1; j<32; j++){
            printf("%8.5f,", x[(N-1)*(i*nby32-1)+j*nby32]);
        }
        printf("     0.0,\n");
    }
    printf("\n");
    for (i=0; i<=32; i++){
        printf("     0.0,");
    }

}
/* --------------------------------------------------------------------------- */
double *allocate_vector(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *X;
    X = (double *) malloc((N+1)*sizeof(double));
    return X;
}
/* --------------------------------------------------------------------------- */
double **allocate_matrix(int N, int M){
    /* Yadu Bhageria, 00733164, M3SC */

    //The safe approach; better sizes over 2^27 in size
    double ** A;
    A=(double **) malloc((N+1)*sizeof(double *));
    for(int i=1; i<N+1; i++){
        A[i]=(double *) malloc((M+1)*sizeof(double));
    }
    return A;
/*
    //The cautious approach:
    double **A; int i;
    A = (double **)malloc((N+1)*sizeof(double *));
    A[0] = (double *)malloc((N*M+1)*sizeof(double));
    A[1] = A[0];
    for (i=2; i<=N; i++) A[i] = A[i-1]+M;
    return A;
*/
}
/* --------------------------------------------------------------------------- */
double **Sn_matrix(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    double **A = allocate_matrix(N-1,N-1);
    for (i=1; i<N; i++){
        for (j=1; j<N; j++){
            A[i][j] = sin(M_PI*i*j/N);
        }
    }
    return A;
}
/* --------------------------------------------------------------------------- */
double **Tn_matrix(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    double **A = allocate_matrix(N,N);
    for (i=1; i<=N; i++){
        for (j=1; j<=N; j++){
            A[i][j] = sin((2.*i-1.)*j*M_PI/(2.*N));
        }
    }
    return A;
}
/* --------------------------------------------------------------------------- */
double **Tnt_matrix(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    double **A = allocate_matrix(N,N);
    for (i=1; i<=N; i++){
        for (j=1; j<=N; j++){
            A[j][i] = sin((2.*i-1.)*j*M_PI/(2.*N));
        }
    }
    return A;
}
/* --------------------------------------------------------------------------- */
double **Un_matrix(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    int i,j;
    double **A = allocate_matrix(N,N);
    for (i=1; i<=N; i++){
        for (j=1; j<=N; j++){
            A[i][j] = sin((2.*i-1.)*(2.*j-1.)*M_PI/(4.*N));
        }
    }
    return A;
}
/* --------------------------------------------------------------------------- */
double ** multiply_square_matrices(double **A, double **B, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double **X = allocate_zero_matrix(N,N);

    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            for (int k=1; k<=N; k++){
                X[i][j] += A[i][k]*B[k][j];
            }
            /* For neater printing */
            if (fabs(X[i][j]) < 100.*DBL_EPSILON){
                X[i][j] = 0.;
            }
        }
    }
    return X;
}
/* --------------------------------------------------------------------------- */
double * multiply_matrix_vector(double **A, double *B, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double *X = allocate_zero_vector(N);

    for (int i=1; i<=N; i++){
        for (int k=1; k<=N; k++){
            X[i] += A[i][k]*B[k];
        }
        /* For neater printing */
        if (fabs(X[i]) < 100.*DBL_EPSILON){
            X[i] = 0.;
        }
    }
    return X;
}
