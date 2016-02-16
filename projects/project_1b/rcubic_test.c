#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"
#include "rcubic_roots.h"

double rcubic_value(double a2, double a1, double a0, double x){
    return (x*x*x + a2*x*x + a1*x + a0);
}
double diffrcubic_value(double a2, double a1, double a0, double x){
    double three=3,two=2;
    return (three*x*x + two*a2*x + a1);
}

int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    double zero=0,one=1,two=2,three=3;
    double alpha,beta,p,yn,yn1,diff,diff1;
    int count,quad_case;

/* Only case where the reduction is not possible is when alpha = 0
=> a2=a1=a0=0. So we deal with this case first. */
    if (a2 == zero & a1 == zero & a0 == zero) {
        *r1=zero;
        return(1);
    }
    beta=-a2/three;
    alpha=cbrt(two*beta*beta*beta - a1*beta - a0); //can change to pow(z,1/3) if not using c11
    p=(three*beta*beta-a1)/(alpha*alpha);
    if (p==zero){yn=one;}
    else {
        if (p>11.0/three){yn=sqrt(p);} else if (p<-1.92) {yn=-1.0/p;} else {yn=1.0 + p/3.0 - (p*p*p)/81.0;} //set starting value of p
        yn1 = yn - rcubic_value(zero,-p,-one,yn)/diffrcubic_value(zero,-p,-one,yn);
        /* printf("%g\n", diff1); */
        while (yn!=yn1 && ( count<=3 || diff1 < diff )) {
            yn=yn1;
            yn1 = yn - rcubic_value(zero,-p,-one,yn)/diffrcubic_value(zero,-p,-one,yn);
            diff1 = fabs(yn-yn1);
            diff = diff1;
            count = count + 1;
            /* printf("count: %d\n", count); */
            /* printf("yn = %.10g, yn+1 = %.10g\n", yn,yn1); */
        }
    } *r1= alpha*yn + beta;
    /*printf("Note: one root found has been found using the Newtom Rapheson approximation method.\n");
    One real root has been found. Now we use our quadratic formula
    to find the other roots and return the appropriate value */
    quad_case = quad_roots(one,a2+(*r1),-a0/(*r1),r2,r3);
    switch (quad_case) {
        case 0: return(0);
        case 1: if (r1==r2){return(1);} else {return(2);}
        case 2: order_3(r1,r2,r3); if (r1==r2){return(2);} else if (r2==r3){return(2);} else {return(3);}
        /* In case 2 r1 cannot equal r3 as r1,r2,r3 are ordered and hence we would have dealt with that in case 1 */
    }
    printf("Error!\n");
    return(-1); //error
}
