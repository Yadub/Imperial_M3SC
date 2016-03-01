#include <float.h> //for DBL_EPSILON
#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void order_2(double *, double *);
int quad_roots(double, double, double, double *, double *);
/* -Functions-implemented-in-current-file------------------------------------- */
void order_3(double *, double *, double *);
void set_starting_y0(double, double *);
double iterate_y(double, double );
double newton_rapheson(double );
int roots_of_unity(double, double *, double *, double *);
int roots_return(double, double, double, double *, double *, double *);
int rcubic_roots(double, double, double, double *, double *, double *);
/* --------------------------------------------------------------------------- */

/* Cubic Solver using the Newton-Rapheson approximation for the first real root*/
int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    /* Bhageria, Yadu, M3SC */
    double zero=0,one=1,two=2,three=3;
    double alpha,beta,p,y,alpha_coef;
    double p2=3.0*cbrt(0.25),y2 = -cbrt(0.5);;

    if (a2 == zero && a1 == zero && a0 == zero) { /* a2=a1=a0=0. So x^3 = 0 => r1=r2=r3=0 */
        *r1=zero;
        return(1);
    } else if (a2 == zero && a1 == zero) { /* Part 3 i */
        return(roots_of_unity(cbrt(-a0),r1,r2,r3));
    } else if (a0 == zero) { /* Part 3 ii */
        *r1 = zero;
        return(roots_return(one,a2,a1,r1,r2,r3));
    } else if (fabs(a0-a1*a2)<DBL_EPSILON){ /* Part 3 iii */
        *r1 = -a2;
        if (a1>zero){
            *r2 = zero;
            *r3 = sqrt(a1);
            return(0);
        } else {
            *r2 = sqrt(-a1);
            *r3 = -sqrt(-a1);
            order_3(r1,r2,r3);
            return *r1==*r2 || *r2==*r3 ? 2 : 3;
        }
    } else if ( fabs(3.0*a1-a2*a2) < DBL_EPSILON && fabs(27.0*a0-a2*a2*a2) < DBL_EPSILON ){ /* Part 3 iv */
        *r1 = -a2/3.0;
        return(1);
    }

    beta=-a2/three;
    if (fabs(beta)>one) {
        alpha_coef = cbrt(two - (a1/beta)/beta - ((a0/beta)/beta)/beta );
        alpha = beta * alpha_coef;
        p = (three-(a1/beta)/beta)/(alpha_coef*alpha_coef);
    } else {
        alpha = cbrt(two*beta*beta*beta - a1*beta - a0);
        p = (three*beta*beta-a1)/(alpha*alpha);
    }
    if (alpha == zero){ /* When our degeneration doesn't makes sense */
        *r1 = beta;
        return(roots_return(one,-two*beta,-two*beta*beta+a1,r1,r2,r3));
    } else if ( fabs(p - p2) < 10.0*DBL_EPSILON && fabs(1.0/alpha) > 10*DBL_EPSILON){ /* Part 3 v: we choose 10.0*DBL_EPSILON as we loose accuracy in the calculation of alpha, beta, and p. */
        *r1 = alpha*y2 + beta;
        *r2 = alpha*y2 + beta;
        *r3 = alpha/(y2*y2) + beta;
        order_3(r1,r2,r3);
        return *r1==*r2 || *r2==*r3 ? 2 : 3;
    } else if (p==zero) {
        roots_of_unity(one,r1,r2,r3);
        *r1 = alpha * (*r1) + beta;
        *r2 = alpha * (*r2) + beta;
            return(0);
    } else {
        y=newton_rapheson(p);
        *r1= alpha*y + beta;
    }
    *r1 = fabs(*r1)<10*DBL_EPSILON ? 0.0 : *r1;
    return(roots_return(one, a2+(*r1), (*r1==zero)? a1 : -a0/(*r1) , r1, r2, r3));
}
/* --------------------------------------------------------------------------- */

/* finds yn+1 for given yn and p */
double iterate_y(double p, double y){
    /* Bhageria, Yadu, M3SC */
    return(y-(y*y*y-p*y-1.0)/(3.0*y*y-p));
}
/* --------------------------------------------------------------------------- */

/* Sets starting value of yn based on p */
void set_starting_y0(double p, double *y0){
    /* Bhageria, Yadu, M3SC */
    if (p>11.0/3.0){*y0=sqrt(p);}
    else if (p<-1.92) {*y0=-1.0/p;}
    else {*y0=1.0 + p/3.0 - (p*p*p)/81.0;}
}
/* --------------------------------------------------------------------------- */

/* Computes first real root using the Newton-Rapheson approximation method */
double newton_rapheson(double p){
    /* Bhageria, Yadu, M3SC */
    double zero=0,one=1,yn,yn1,diff,diff1;
    int count=1;
    if (p==zero){yn1=one;}
    else {
        set_starting_y0(p,&yn);
        yn1 = iterate_y(p,yn);
        while ( count < 4 || (fabs(yn-yn1)>DBL_EPSILON && diff1 < diff) ){
            yn=yn1;
            yn1 = iterate_y(p,yn);
            diff1 = fabs(yn-yn1);
            diff = diff1;
            count = count + 1;
            /* printf("yn = %.10g, yn+1 = %.10g\n", yn,yn1); //to test */
        }
    }
    return(yn1);
}
/* --------------------------------------------------------------------------- */

/* Computes r2 and r3 once r1 has been found. Returns an integer corresponding to the number of real roots found */
int roots_return(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    /* Bhageria, Yadu, M3SC */
    int quad_case = quad_roots(a2,a1,a0,r2,r3);
    switch (quad_case) {
        case 0: return(0);
        case 1: return r1==r2 ? 1 : 2;
        case 2: order_3(r1,r2,r3); if (r1==r2){return(2);} else {return r2==r3 ? 2 : 3;}
        /* In case 2 r1 cannot equal r3 as r1,r2,r3 are ordered and hence we would have dealt with that in case 1 */
    }
    return(-1); /* for errors */
}
/* --------------------------------------------------------------------------- */

int roots_of_unity(double r, double *r1, double *r2, double *r3){
    /* Bhageria, Yadu, M3SC */
    *r1 = r; //Real Root
    *r2 = r/2.0; //Real Part of Complex Roots
    *r3 = fabs(r)*sqrt(3.0)/2.0; //Positive Imaginary Part of Complex Roots
    return(0);
}
/* --------------------------------------------------------------------------- */
void order_3(double *r1, double *r2, double *r3) {
	/* Bhageria, Yadu, M3SC */
    order_2(r1,r3);
    order_2(r1,r2);
    order_2(r2,r3);
}
/* --------------------------------------------------------------------------- */
