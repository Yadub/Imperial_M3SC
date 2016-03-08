#include <float.h> //for DBL_EPSILON
#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void order(double *, int);
int quad_roots(double *, double *);
/* -Functions-implemented-in-current-file------------------------------------- */
void set_starting_y0(double, double *);
double iterate_y(double, double );
double newton_rapheson(double );
int roots_of_unity(double, double *);
int roots_return(double, double, double, double *);
int rcubic_roots(double *, double *);
/* --------------------------------------------------------------------------- */

/* Cubic Solver using the Newton-Rapheson approximation for the first real root*/
int rcubic_roots(double *a, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    double zero=0,one=1,two=2,three=3;
    double alpha,beta,p,y,alpha_coef;
    double p2=3.0*cbrt(0.25),y2 = -cbrt(0.5);

    if (a[2] == zero && a[1] == zero && a[0] == zero) { /* a[2]=a[1]=a[0]=0. So x^3 = 0 => root[1]=root[2]=root[3]=0 */
        root[1]=zero;
        return(1);
    } else if (a[2] == zero && a[1] == zero) { /* Part 3 i */
        return(roots_of_unity(cbrt(-a[0]),root));
    } else if (a[0] == zero) { /* Part 3 ii */
        root[1] = zero;
        return(roots_return(one,a[2],a[1],root));
    } else if (fabs(a[0]-a[1]*a[2])<DBL_EPSILON){ /* Part 3 iii */
        root[1] = -a[2];
        if (a[1]>zero){
            root[2] = zero;
            root[3] = sqrt(a[1]);
            return(0);
        } else {
            root[2] = sqrt(-a[1]);
            root[3] = -sqrt(-a[1]);
            order(root,3);
            return root[1]==root[2] || root[2]==root[3] ? 2 : 3;
        }
    } else if ( fabs(3.0*a[1]-a[2]*a[2]) < DBL_EPSILON && fabs(27.0*a[0]-a[2]*a[2]*a[2]) < DBL_EPSILON ){ /* Part 3 iv */
        root[1] = -a[2]/3.0;
        return(1);
    }

    beta=-a[2]/three;
    if (fabs(beta)>one) {
        alpha_coef = cbrt(two - (a[1]/beta)/beta - ((a[0]/beta)/beta)/beta );
        alpha = beta * alpha_coef;
        p = (three-(a[1]/beta)/beta)/(alpha_coef*alpha_coef);
    } else {
        alpha = cbrt(two*beta*beta*beta - a[1]*beta - a[0]);
        p = (three*beta*beta-a[1])/(alpha*alpha);
    }

    if (alpha == zero){ /* When our degeneration doesn't makes sense */
        root[1] = beta;
        return(roots_return(one,-two*beta,-two*beta*beta+a[1],root));
    } else if ( fabs(p - p2) < 10.0*DBL_EPSILON && fabs(1.0/alpha) > 10e-10){ /* Part 3 v: we choose 10.0*DBL_EPSILON as we loose accuracy in the calculation of alpha, beta, and p. */
        root[1] = alpha*y2 + beta;
        root[2] = alpha*y2 + beta;
        root[3] = alpha/(y2*y2) + beta;
        order(root,3);
        return root[1]==root[2] || root[2]==root[3] ? 2 : 3;
    } else if (p==zero) {
        roots_of_unity(one,root);
        root[1] = alpha * (root[1]) + beta;
        root[2] = alpha * (root[2]) + beta;
        root[3] = fabs(alpha * root[3]);
            return(0);
    } else {
        y=newton_rapheson(p);
        root[1]= alpha*y + beta;
    }
    root[1] = fabs(root[1])<10*DBL_EPSILON ? 0.0 : root[1];
    return(roots_return(one, a[2]+(root[1]), (root[1]==zero)? a[1] : -a[0]/(root[1]) , root));
}
/* --------------------------------------------------------------------------- */

/* finds yn+1 for given yn and p */
double iterate_y(double p, double y){
    /* Bhageria, Yadu, 00733164, M3SC */
    return(y-(y*y*y-p*y-1.0)/(3.0*y*y-p));
}
/* --------------------------------------------------------------------------- */

/* Sets starting value of yn based on p */
void set_starting_y0(double p, double *y0){
    /* Bhageria, Yadu, 00733164, M3SC */
    if (p>11.0/3.0){*y0=sqrt(p);}
    else if (p<-1.92) {*y0=-1.0/p;}
    else {*y0=1.0 + p/3.0 - (p*p*p)/81.0;}
}
/* --------------------------------------------------------------------------- */

/* Computes first real root using the Newton-Rapheson approximation method */
double newton_rapheson(double p){
    /* Bhageria, Yadu, 00733164, M3SC */
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

/* Computes root[2] and root[3] once root[1] has been found. Returns an integer corresponding to the number of real roots found */
int roots_return(double a2, double a1, double a0, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    double b[3];
    b[0] = a0;
    b[1] = a1;
    b[2] = a2;
    int quad_case = quad_roots(b,root+1);
    switch (quad_case) {
        case 0: return(0);
        case 1: return root[1]==root[2] ? 1 : 2;
        case 2: order(root,3); if (root[1]==root[2]){return(2);} else {return root[2]==root[3] ? 2 : 3;}
        /* In case 2 root[1] cannot equal root[3] as root[1],root[2],root[3] are ordered and hence we would have dealt with that in case 1 */
    }
    return(-1); /* for errors */
}
/* --------------------------------------------------------------------------- */

int roots_of_unity(double r, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    root[1] = r; //Real Root
    root[2] = -r/2.0; //Real Part of Complex Roots
    root[3] = fabs(r)*sqrt(3.0)/2.0; //Positive Imaginary Part of Complex Roots
    return(0);
}
/* --------------------------------------------------------------------------- */
