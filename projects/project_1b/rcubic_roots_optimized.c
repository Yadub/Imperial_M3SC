#include <float.h>
#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"
#include "rcubic_roots_optimized.h"

void set_starting_y0(double, double *);
double iterate_y(double, double );
double newton_rapheson(double );
int roots_of_unity(double, double *, double *, double *);
int roots_return(double, double, double, double *, double *, double *);
int rcubic_roots(double, double, double, double *, double *, double *);

/* Cubic Solver using the Newton-Rapheson approximation for the first real root */
int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    double zero=0,one=1,two=2,three=3;
    double alpha,beta,p,y;
    double epsilon=1e-13,p2=3.0*cbrt(0.25),y2 = -cbrt(0.5);;

    if (a2 == zero && a1 == zero && a0 == zero) { /* a2=a1=a0=0. So x^3 = 0 => r1=r2=r3=0 */
        *r1=zero;
        return(1);
    } else if (a2 == zero && a1 == zero) { /* Part 3 i */
        return(roots_of_unity(-cbrt(a0),r1,r2,r3));
    }

    beta=-a2/three;
    alpha=cbrt(two*beta*beta*beta - a1*beta - a0); /* Can change to pow(z,1/3) if not using c11 */
    p=(three*beta*beta-a1)/(alpha*alpha);

    if (a0==zero){ /* Part 3 ii */
        *r1 = zero;
    } else if (a0==a1*a2){ /* Part 3 iii */
        *r1 = -a2;
        if (a1>zero){
            *r2 = zero;
            *r3 = sqrt(a1);
            return(0);
        } else {
            *r2 = sqrt(-a1);
            *r3 = -sqrt(a1);
            order_3(r1,r2,r3);
            return *r1==*r2 || *r2==*r3 ? 2 : 3;
        }
    } else if ( 3.0*a1==a2*a2  && 27.0*a0==a2*a2*a2 ){ /* Part 3 iv */
        *r1 = a2/3.0;
        return(1);
    } else if (alpha == zero){ /* When our degeneration doesn't makes sense */
        *r1 = beta;
        return(roots_return(one,-two*beta,-two*beta*beta+a1,r1,r2,r3));
    } else if ( fabs( p - p2) < epsilon ){ /* Part 3 v */
            *r1 = alpha*y2 + beta;
            *r2 = alpha*y2 + beta;
            *r3 = alpha/(y2*y2) + beta;
            order_3(r1,r2,r3);
            return *r1==*r2 || *r2==*r3 ? 2 : 3;
    } else {
        y=newton_rapheson(p);
        *r1= alpha*y + beta;
    }
    return(roots_return(one,a2+(*r1),-a0/(*r1),r1,r2,r3));
}

/* finds yn+1 for given yn and p */
double iterate_y(double p, double y){
    double one=1,three=3;
    return(y-(y*y*y-p*y-one)/(three*y*y-p));
}

/* Sets starting value of yn based on p */
void set_starting_y0(double p, double *y0){
    if (p>11.0/3.0){*y0=sqrt(p);}
    else if (p<-1.92) {*y0=-1.0/p;}
    else {*y0=1.0 + p/3.0 - (p*p*p)/81.0;}
}

/* Computes first real root using the Newton-Rapheson approximation method */
double newton_rapheson(double p){
    double zero=0,one=1,yn,yn1,diff,diff1;
    int count=1;
    if (p==zero){yn1=one;}
    else {
        set_starting_y0(p,&yn);
        yn1 = iterate_y(p,yn);
        while (yn!=yn1 && ( count<4 || diff1 < diff )) {
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

/* Computes r2 and r3 once r1 has been found. Returns an integer corresponding to the number of real roots found */
int roots_return(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    int quad_case = quad_roots(a2,a1,a0,r2,r3);
    switch (quad_case) {
        case 0: return(0);
        case 1: if (r1==r2){return(1);} else {return(2);}
        case 2: order_3(r1,r2,r3); if (r1==r2){return(2);} else if (r2==r3){return(2);} else {return(3);}
        /* In case 2 r1 cannot equal r3 as r1,r2,r3 are ordered and hence we would have dealt with that in case 1 */
    }
    return(-1); /* for errors */
}

int roots_of_unity(double r, double *r1, double *r2, double *r3){
    *r1 = r;
    *r2 = r/2.0;
    *r3 = r*sqrt(3.0)/2.0;
    return(0);
}
