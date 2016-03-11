#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Yadu Bhageria, 00733164, M3SC */

/* -Functions-needed-from-other-files----------------------------------------- */

/* -Functions-implemented-in-current-file------------------------------------- */
void print_statements();
void print_matrix(double **, int );
double *Gauss(double **, double *, int);
/* --------------------------------------------------------------------------- */

double *Gauss(double **a, double *b, int N){
    /* Yadu Bhageria, 00733164, M3SC */
    //double * x = y;
    //double * y_temp = y;
    //double ** A_temp = A;
    //mint i,j,k;
    print_vector(b,N);
    print_matrix(a,N);
    int   i,j,k,m,rowx;
    double xfac,temp,temp1,amax;
    rowx = 0;   /* Keep count of the row interchanges */
    for (k=1; k<=N-1; ++k) {

         amax = (double) fabs(a[k][k]) ;
         m = k;
         for (i=k+1; i<=N; i++){   /* Find the row with largest pivot */
                   xfac = (double) fabs(a[i][k]);
                   if(xfac > amax) {amax = xfac; m=i;}
         }
         if(m != k) {  /* Row interchanges */
                     rowx = rowx+1;
                     temp1 = b[k];
                     b[k]  = b[m];
                     b[m]  = temp1;
                     for(j=k; j<=N; j++) {
                           temp = a[k][j];
                           a[k][j] = a[m][j];
                           a[m][j] = temp;
                     }
          }
           for (i=k+1; i<=N; ++i) {
              xfac = a[i][k]/a[k][k];

                   for (j=k+1; j<=N; ++j) {
                       a[i][j] = a[i][j]-xfac*a[k][j];
                   }
              b[i] = b[i]-xfac*b[k];
           }
   }
    print_matrix(a,N);
    //Start subbing back in
    //TBD
    return(b);
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
            printf("%4g ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
