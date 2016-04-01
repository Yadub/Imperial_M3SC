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
/* A cautious but slower approach

        w[N*skip] = y[skip*N/2];
        for (int i=1; i<N/2; i++){
            w[skip*2*i] = y[skip*i] + y[skip*(N-i)];
            w[skip*(2*(i-1)+1)] = y[skip*i] - y[skip*(N-i)];
        }
        y[N*skip] = w[N*skip];
        for (int i=1; i<N/2; i++){
            y[skip*2*i] = w[skip*2*i];
            y[skip*(2*(i-1)+1)] = w[skip*(2*(i-1)+1)];
        }
        int e1 = FastSN(x,y-skip,w-skip,S,N/2,2*skip);
        int e2 = FastTN(x-skip,y,w,S,N/2,2*skip);
        returnval = (e1==0 && e2==0)? 0 : -1;
*/
        w[N*skip] = y[skip*N/2];
        for (int i=1; i<N/2; i++){
            w[skip*2*i] = y[skip*i] + y[skip*(N-i)];
        }
        int e2 = FastTN(x-skip,w,w-skip,S,N/2,2*skip);
        for (int i=1; i<N/2; i++){
            w[skip*(2*(i-1)+1)] = y[skip*i] - y[skip*(N-i)];
        }
        int e1 = FastSN(x,w-skip,w,S,N/2,2*skip);
        returnval = (e1==0 && e2==0)? 0 : -1;
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
    int returnval = 0;
    //printf("in Tn: N=%3d, skip=%3d \n",N,skip);
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
        int e1 = FastTN(w,y,x,S,N/2,2*skip);
        int e2 = FastUN(w-skip,y-skip,x-skip,S,N/2,2*skip);
        for (int i=1; i<=N/2; i++){
            x[i*skip] = w[(2*i-1)*skip] + w[2*i*skip];
            x[(N+1-i)*skip] = w[(2*i-1)*skip] - w[2*i*skip];
        }
        returnval = (e1==0 && e2==0)? 0 : -1;
    } /*else if (N % 3 == 0){

    } else if (N % 5 == 0){

    } */else{
        return -1;
    }
    return returnval;
}
/* --------------------------------------------------------------------------- */
int FastUN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
    //printf("in Un: N=%3d, skip=%3d \n",N,skip);
    int returnval = 0;
/*
    Check the input is valid
*/

    if (N==0){
        return -1;
    } else if (N==1){
        x[skip] = sin(M_PI*1./4.)*y[skip];
    } else if (N==2){
        x[skip] = sin(M_PI*1./8.)*y[skip] + sin(M_PI*3./8.)*y[2*skip];
        x[2*skip] = sin(M_PI*3./8.)*y[skip] - sin(M_PI*1./8.)*y[2*skip];
        /*
        // If the inputted S is big enough
        x[skip] = S[3]*y[skip] + S[4]*y[2*skip];
        x[2*skip] = S[4]*y[skip] - S[3]*y[2*skip];
        */
    } else if (N % 2 == 0){
        int i;
        /* Find values of vector a */
        for (i=1; i<N/2; i++){
            w[skip*2*i] = y[(N+1-2*i)*skip] - y[(N-2*i)*skip];
        }
        w[skip*N] = y[skip];
        int e2 = FastTN(w-skip,w,w-skip,S,N/2,2*skip);
        for (i=1; i<=N/2; i++){
            //Use vector S here insteal!
            x[i*skip] = sin((2*i-1)*M_PI/(4*N))*pow(-1,i+1)*w[(2*i-1)*skip];
            x[(N+1-i)*skip] = sin((2*N+1-2*i)*M_PI/(4*N))*pow(-1,i+1)*w[(2*i-1)*skip];
        }
        /* Find values of vector b */
        for (i=1; i<N/2; i++){
            w[skip*(2*(i-1)+1)] = y[(2*i)*skip] + y[(2*i+1)*skip];
        }
        w[skip*(N-1)] = y[N*skip];
        int e1 = FastTN(w,w-skip,w,S,N/2,2*skip);
        for (i=1; i<=N/2; i++){
            //Use vector S here insteal!
            x[i*skip] += sin((2*N+1-2*i)*M_PI/(4*N))*w[(2*i)*skip];
            x[(N+1-i)*skip] -= sin((2*i-1)*M_PI/(4*N))*w[(2*i)*skip];
        }
        returnval = (e1==0 && e2==0)? 0 : -1;
        //Call half fast Sn and deal with stuff.
    } /*else if (N % 3 == 0){

    } else if (N % 5 == 0){

    } */else{
        return -1;
    }

    return returnval;

}
