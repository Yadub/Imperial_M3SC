/* Yadu Bhageria, 00733164, M3SC */
#include <stdio.h>
#include <math.h>
/*incase Pi is not defined */
#ifndef M_PI
#    define M_PI acos(-1.)
#endif
/* -Functions-needed-from-other-files----------------------------------------- */
double *allocate_vector(int);
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
    if (N%3==0){
        denominator = 3.;
        S = allocate_vector(N/3);
        for (int i=1; i<=N/3; i++){
            if (numerator/denominator >= 1./2.){
                numerator = 1.;
                denominator *= 2.;
            }
            S[i] = sin(M_PI*numerator/denominator);
            numerator += 2.;
        }
    } else if (N%5==0){
        denominator = 10.;
        S = allocate_vector(N/5);
        S[1] = sin(M_PI*1./5.);
        S[2] = sin(M_PI*2./5.);
        for (int i=1; i<=(-2+N/5); i++){
            if (numerator/denominator >= 1./2.){
                numerator = 1.;
                denominator *= 2.;
            }
            //printf("%d: %d/%d\n", i+2, (int)numerator, (int)denominator);
            S[i+2] = sin(M_PI*numerator/denominator);
            numerator += 2.;
        }
    } else if (N%2==0){
        denominator = 2.;
        S = allocate_vector(N/2);
        for (int i=1; i<=N/2; i++){
            if (numerator/denominator >= 1./2.){
                numerator = 1.;
                denominator *= 2.;
            }
            S[i] = sin(M_PI*numerator/denominator);
            numerator += 2.;
        }
    } else { //for when S is neither of the wanted values
        S = allocate_vector(1);
        S[1] = 0.;
    }
    S[0] = 1.;
    return S;
}
/* --------------------------------------------------------------------------- */
int FastSN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
    int returnval = 0;
/*
    Check the input is valid
*/
    if (N<=1){
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
        e2 = FastTN(x-skip,w-skip,y-skip,S,N/2,2*skip);
        returnval = (e1==0 && e2==0)? 0 : -1;
    } else{
        returnval = -1;
    }
    return returnval;

}
/* --------------------------------------------------------------------------- */
int FastTN(double *x, double *y, double *w, double *S,int N, int skip){
    /* Yadu Bhageria, 00733164, M3SC */
    int returnval = 0;
#ifdef DEBUG
    printf("in Tn: N=%3d, skip=%3d \n",N,skip);
#endif
    /*
        Check the input is valid
    */
    if (N<=0){
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
        int e2 = FastUN(w-skip,y-skip,x-skip,S,N/2,2*skip);
        for (int i=1; i<=N/2; i++){
            x[i*skip] = w[(2*i-1)*skip] + w[2*i*skip];
            x[(N+1-i)*skip] = w[(2*i-1)*skip] - w[2*i*skip];
        }
        returnval = (e1==0 && e2==0)? 0 : -1;
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
/*
    Check the input is valid
*/
    if (N<=0){
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

        // /* Find values of vector a */
        // for (i=1; i<N/2; i++){
        //     w[skip*2*i] = y[(N+1-2*i)*skip] - y[(N-2*i)*skip];
        // }
        // w[skip*N] = y[skip];
        // int e2 = FastTN(w-skip,w,x-skip,S,N/2,2*skip);
        // for (i=1; i<=N/2; i++){
        //     x[i*skip] = S[N+i-1]*pow(-1,i+1)*w[(2*i-1)*skip];
        //     x[(N+1-i)*skip] = S[2*N-i]*pow(-1,i+1)*w[(2*i-1)*skip];
        // }
        // /* Find values of vector b */
        // for (i=1; i<N/2; i++){
        //     w[skip*(2*(i-1)+1)] = y[(2*i)*skip] + y[(2*i+1)*skip];
        // }
        // w[skip*(N-1)] = y[N*skip];
        // int e1 = FastTN(w,w-skip,y,S,N/2,2*skip);
        // for (i=1; i<=N/2; i++){
        //     x[i*skip] += S[2*N-i]*w[(2*i)*skip];
        //     x[(N+1-i)*skip] -= S[N+i-1]*w[(2*i)*skip];
        // }
        for (i=1; i<N/2; i++){
            w[skip*2*i] = y[(N+1-2*i)*skip] - y[(N-2*i)*skip];
            w[skip*(2*(i-1)+1)] = y[(2*i)*skip] + y[(2*i+1)*skip];
        }
        w[skip*N] = y[skip];
        w[skip*(N-1)] = y[N*skip];
        int e2 = FastTN(y-skip,w,x-skip,S,N/2,2*skip);
        int e1 = FastTN(y,w-skip,x,S,N/2,2*skip);
        for (i=1; i<=N/2; i++){
            if (i%2==0){
                x[i*skip] = -S[N+i-1] * y[(2*i-1)*skip] + S[2*N-i]*y[(2*i)*skip];
                x[(N+1-i)*skip] = -S[2*N-i] * y[(2*i-1)*skip] - S[N+i-1]*y[(2*i)*skip];
            } else{
            x[i*skip] = S[N+i-1] * y[(2*i-1)*skip] + S[2*N-i]*y[(2*i)*skip];
            x[(N+1-i)*skip] = S[2*N-i] * y[(2*i-1)*skip] - S[N+i-1]*y[(2*i)*skip];
            }
        }
        returnval = (e1==0 && e2==0)? 0 : -1;
    } else{
        returnval = -1;
    }
    return returnval;
}
