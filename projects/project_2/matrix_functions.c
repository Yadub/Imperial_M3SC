#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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
            printf("%3.1g ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/* --------------------------------------------------------------------------- */
void print_vector(double *x, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    for (int i=1; i<N+1; i++){
        printf("%3d | %12.4g\n",i, x[i]);
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
double **allocate_matrix(int N, int M){
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
double *make_Yvec1D(int N, bool smooth, double delta2){
    /* Yadu Bhageria, 00733164, M3SC */
    double *Y = allocate_zero_vector(N-1);
    for (int i=1; i<N; i++){
        if ( (double)i/N == 0.5 || (double)i/N == 0.25){
            if (smooth == true){
                Y[i] = -40.0;
            } else{
            Y[i] = -80.0;
            }
        } else if ((double)i/N <= 0.5 && (double)i/N >= 0.25){
            Y[i] = -80.0;
        } else{Y[i] = 0.0;}
        Y[i] *= delta2;
    }
    return Y;
}
/* --------------------------------------------------------------------------- */
double **make_AGauss1D(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double **A = allocate_matrix(N-1,N-1);
    for (int i=1; i<=N-1; i++){
        A[i][i] = -2.0;
        if (i>1){
            A[i][i-1] = 1.0;
        }
        if (i<N-1){
            A[i][i+1] = 1.0;
        }
    }
    return A;
}
/* --------------------------------------------------------------------------- */
double **make_ABGauss1D(int N, int B){
    /* Yadu Bhageria, 00733164, M3SC */
    double **A = allocate_matrix(N-1,2*B+1);

    for (int i=1; i<=N-1; i++){
        A[i][B+1] = -2.0;
        A[i][B+2] = A[i][B] = 1.0;
    }
    return A;
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
