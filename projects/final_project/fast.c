/* Yadu Bhageria, 00733164, M3SC */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* incase Pi is not defined */
#ifndef M_PI
#    define M_PI acos(-1.)
#endif
/* -Functions-implemented-in-current-file------------------------------------- */
double *SFactors(int);
int FastSN(double *, double *, double *, double *,int, int);
int FastTN(double *, double *, double *, double *,int, int);
int FastUN(double *, double *, double *, double *,int, int);
/* --------------------------------------------------------------------------- */
double *SFactors(int N){
    /* Yadu Bhageria, 00733164, M3SC */
    double numerator = 1., denominator;
    double *S;

    if (N%5==0){
        denominator = 10.;
        S = (double *) malloc((N/2+1)*sizeof(double));
        S[1] = sin(M_PI*1./5.);
        S[2] = sin(M_PI*2./5.);
        for (int i=1; i<=(-2+N/2); i++){
            if (numerator/denominator >= 1./2.){
                numerator = 1.;
                denominator *= 2.;
            }
            S[i+2] = sin(M_PI*numerator/denominator);
            numerator += 2.;
        }
    } else if (N%3==0 || N%2==0){
        denominator = (N%3==0) ? 3. : 2.;
        S = (double *) malloc((N/2+1)*sizeof(double));
        for (int i=1; i<=N/2; i++){
            if (numerator/denominator >= 1./2.){
                numerator = 1.;
                denominator *= 2.;
            }
            S[i] = sin(M_PI*numerator/denominator);
            numerator += 2.;
        }
    } else { //When N is not divisible by 2, 3, or 5
        S = (double *) malloc(2*sizeof(double));
        S[1] = 0.;
    }
    S[0] = 1.; //Given
    return S;
}
/* --------------------------------------------------------------------------- */
int FastSN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
#ifdef DEBUG
    printf("in Sn: N=%3d, skip=%3d \n",N,skip);
#endif

    int returnval = 0;

    if (N<=1){ //Check N is sensible
        returnval = -1;
    } else if (N==2){
        x[skip] = y[skip];
    } else if (N==3){
        x[  skip] = S[1] * (y[skip] + y[2*skip]);
        x[2*skip] = S[1] * (y[skip] - y[2*skip]);
    } else if (N==5){
        double t1, t2;
        t1 = S[1]*y[  skip] + S[2]*y[3*skip];
        t2 = S[2]*y[2*skip] + S[1]*y[4*skip];
        x[  skip] = t1 + t2;
        x[4*skip] = t1 - t2;
        t1 = S[2]*y[  skip] - S[1]*y[3*skip];
        t2 = S[1]*y[2*skip] - S[2]*y[4*skip];
        x[2*skip] = t1 + t2;
        x[3*skip] = t1 - t2;
    } else if (N % 2 == 0){
        int e1, e2;
        w[(N-1)*skip] = y[skip*N/2];
        for (int i=1; i<N/2; i++){
            w[skip*(2*(i-1)+1)] = y[skip*i] + y[skip*(N-i)];
            w[skip*2*i] = y[skip*i] - y[skip*(N-i)];
        }
        e1 = FastSN(x,w,y,S,N/2,2*skip);
        if (e1!=0) return e1;
        e2 = FastTN(x-skip,w-skip,y-skip,S,N/2,2*skip);
        if (e1!=0) return e2;
    } else{
        returnval = -1;
    }
    return returnval;
}
/* --------------------------------------------------------------------------- */
int FastTN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
#ifdef DEBUG
    printf("in Tn: N=%3d, skip=%3d \n",N,skip);
#endif

    int returnval = 0;

    if (N<=0){ //Check N is sensible
        returnval = -1;
    } else if (N==1){
        x[skip] = y[skip];
    } else if (N==2){
        double t1 = S[1]*y[skip];
        x[skip]   = t1 + y[2*skip];
        x[2*skip] = t1 - y[2*skip];
    } else if (N==3){
        double t1 = S[2]*y[skip] + y[3*skip];
        double t2 = S[1]*y[2*skip];
        x[skip]   = t1 + t2;
        x[2*skip] = y[skip] - y[3*skip];
        x[3*skip] = t1 - t2;
    } else if (N==5){
        double t1, t2;
        t1 = S[3]*y[  skip] + S[4]*y[3*skip] + y[5*skip];
        t2 = S[1]*y[2*skip] + S[2]*y[4*skip];
        x[  skip] = t1 + t2;
        x[5*skip] = t1 - t2;
        t1 = S[4]*y[  skip] + S[3]*y[3*skip] - y[5*skip];
        t2 = S[2]*y[2*skip] - S[1]*y[4*skip];
        x[2*skip] = t1 + t2;
        x[4*skip] = t1 - t2;
        x[3*skip] = y[skip] - y[3*skip] + y[5*skip];
    } else if (N % 2 == 0){
        int e1 = FastTN(w,y,x,S,N/2,2*skip);
        if (e1!=0) return e1;
        int e2 = FastUN(w-skip,y-skip,x-skip,S,N/2,2*skip);
        if (e2!=0) return e2;
        for (int i=1; i<=N/2; i++){
            x[      i*skip] = w[(2*i-1)*skip] + w[2*i*skip];
            x[(N+1-i)*skip] = w[(2*i-1)*skip] - w[2*i*skip];
        }
    } else{
        returnval = -1;
    }
    return returnval;
}
/* --------------------------------------------------------------------------- */
int FastUN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
#ifdef DEBUG
    printf("in Un: N=%3d, skip=%3d \n",N,skip);
#endif

    int returnval = 0;

    if (N<=0){ //Check N is sensible
        returnval = -1;
    } else if (N==1){
        x[skip] = S[1]*y[skip];
    } else if (N==2){
        x[  skip] = S[2]*y[skip] + S[3]*y[2*skip];
        x[2*skip] = S[3]*y[skip] - S[2]*y[2*skip];
    } else if (N==3){
        double t1 = S[4]*y[2*skip];
        x[  skip] = S[3]*y[skip] + S[5]*y[3*skip] + t1;
        x[2*skip] = S[4]*(y[skip] + y[2*skip] - y[3*skip]);
        x[3*skip] = S[5]*y[skip] + S[3]*y[3*skip] - t1;
    } else if (N==5){
        double t1 = S[7]*y[3*skip];
        x[skip]   = S[5]*y[skip] + S[6]*y[2*skip] + t1 + S[8]*y[4*skip] + S[9]*y[5*skip];
        x[2*skip] = S[6]*y[skip] + S[9]*y[2*skip] + t1 - S[5]*y[4*skip] - S[8]*y[5*skip];
        x[3*skip] = S[7]*(y[skip] + y[2*skip] - y[3*skip] - y[4*skip] + y[5*skip]);
        x[4*skip] = S[8]*y[skip] - S[5]*y[2*skip] - t1 + S[9]*y[4*skip] - S[6]*y[5*skip];
        x[5*skip] = S[9]*y[skip] - S[8]*y[2*skip] + t1 - S[6]*y[4*skip] + S[5]*y[5*skip];
    } else if (N % 2 == 0){
        int i;
        for (i=1; i<N/2; i++){
            w[skip*2*i] = y[(N+1-2*i)*skip] - y[(N-2*i)*skip];
            w[skip*(2*(i-1)+1)] = y[(2*i)*skip] + y[(2*i+1)*skip];
        }
        w[    N*skip] = y[skip];
        w[(N-1)*skip] = y[N*skip];
        int e1 = FastTN(y-skip,w,x-skip,S,N/2,2*skip);
        if (e1!=0) return e1;
        int e2 = FastTN(y,w-skip,x,S,N/2,2*skip);
        if (e2!=0) return e2;
        for (i=1; i<=N/2; i++){
            if (i%2==0){
                x[      i*skip] = -S[N+i-1]*y[(2*i-1)*skip] + S[2*N-i]*y[(2*i)*skip];
                x[(N+1-i)*skip] = -S[2*N-i]*y[(2*i-1)*skip] - S[N+i-1]*y[(2*i)*skip];
            } else{
            x[      i*skip] = S[N+i-1]*y[(2*i-1)*skip] + S[2*N-i]*y[(2*i)*skip];
            x[(N+1-i)*skip] = S[2*N-i]*y[(2*i-1)*skip] - S[N+i-1]*y[(2*i)*skip];
            }
        }
    } else{
        returnval = -1;
    }
    return returnval;
}
