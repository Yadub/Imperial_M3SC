/* Yadu Bhageria, 00733164, M3SC */
#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
double *SFactors(int);
/* -Functions-implemented-in-current-file------------------------------------- */
int FastSN(double *, double *, double *, double *,int, int);
int FastTN(double *, double *, double *, double *,int, int);
int FastUN(double *, double *, double *, double *,int, int);

/* --------------------------------------------------------------------------- */
int FastSN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
    int returnval = 0;
/*
    Check the input is valid
*/

    if (N<=1){
        return -1;
    } else if (N==2){
        x[skip] = y[skip];
    } else if (N % 2 == 0){
        for (int i=1; i<N/2; i++){
            w[skip*2*i] = y[skip*i] + y[skip*(N-i)];
            w[skip*(2*(i-1)+1)] = y[skip*i] - y[skip*(N-i)];
        }
        w[N*skip] = y[skip*N/2];
        int e1 = FastSN(x,w-skip,w-skip,S,N/2,2*skip);
        int e2 = FastTN(x-skip,w,w,S,N/2,2*skip);
        returnval = (e1==0 && e2==0)? 0 : -1;
        //Call half fast Sn and deal with stuff.
    } /*else if (N % 3 == 0){

    } else if (N % 5 == 0){

    } */else{
        return -1;
    }
    return returnval;

}
/* --------------------------------------------------------------------------- */
int FastTN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */

    /*
        Check the input is valid
    */

    if (N==0){
        return -1;
    } else if (N==1){
        x[skip] = y[skip];
    } else if (N==2){
        x[skip] = 0.5*sqrt(2.)*y[skip] + y[2*skip];
        x[2*skip] = 0.5*sqrt(2.)*y[skip] - y[2*skip];
    } else if (N % 2 == 0){
        //Call half fast Sn and deal with stuff.
    } /*else if (N % 3 == 0){

    } else if (N % 5 == 0){

    } */else{
        return -1;
    }
    return 0;
}
/* --------------------------------------------------------------------------- */
int FastUN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */

/*
    Check the input is valid
*/

    if (N==0){
        return -1;
    } else if (N==1){
        x[skip] = y[skip];
    } else if (N==2){
        x[skip] = sin(M_PI*1./8.)*y[skip] + sin(M_PI*3./8.)*y[2*skip];
        x[2*skip] = sin(M_PI*1./8.)*y[skip] - sin(M_PI*3./8.)*y[2*skip];
        /*
        // If the inputted S is big enough
        x[skip] = S[3]*y[skip] + S[4]*y[2*skip];
        x[2*skip] = S[3]*y[skip] - S[4]*y[2*skip];
        */
    } else if (N % 2 == 0){
        //Call half fast Sn and deal with stuff.
    } /*else if (N % 3 == 0){

    } else if (N % 5 == 0){

    } */else{
        return -1;
    }

    return 0;

}
