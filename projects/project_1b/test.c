int rcubic_roots_opt(double a2, double a1, double a0, double *r1, double *r2, double *r3){
    double zero=0,one=1,two=2,three=3;
    double alpha,beta,p,q,r,y0,yn,yn_plus1,yn_div=1e100;
    int count,quad_case;

// for the case x^3 = 0
    if (a2 == zero & a1 == zero & a0 == zero) {
        *r1=zero;
        return(1);

    } else if (a1 == zero & a0 == zero){
        *r1=zero;
        *r2=zero;
        *r3=-a2;
        order_2(r1,r3);
        return(2);
    } else if (a0==zero) {
        *r1=zero;
        quad_case = quad_roots(one,a2,a1,r2,r3);
        switch (quad_case) {
            case 0: return(0);
            case 1: if (r1==r2) {return(1);} else {return(2);}
            case 2: order_3(r1,r2,r3); if (r1==r2){return(2);} else if (r2==r3){return(2);} else {return(3);}
            /* In case 2 r1 cannot equal r3 as r1,r2,r3 are ordered and hence we would have dealt with that in case 1 */
        }
    } else if (a0==a1*a2) {
        *r1=-a2;
        if (a1<zero){ //real roots
            *r2=sqrt(-a1);
            *r3=-sqrt(-a1);
            order_3(r1,r2,r3);
            //add case where one of roots is equal to r1.
            return(3);
        } else{ //imaginary roots
            *r2=zero; //real part
            *r3=sqrt(a1); //imaginary part
            return(0);
        }
    } else{
        //Now we reduce the cubic to the form y^3 - 3py - 1 = 0 and deal with that
        q=(a2*a2-three*a1)/9.0;
        r=(2.0*a2*a2*a2-9.0*a2*a1+27.0*a0)/54.0;
        beta=-a2/three;
        /* Cases to Deal with */
        if (q==zero){ // !NOT NEEDED!
            *r1=cbrt(-two*r)+beta; //real root
            *r2=-cbrt(-two*r)/two + beta; //real part of complex root
            *r3=sqrt(three)*fabs(cbrt(-two*r))/two; //imaginary part of complex root
            return(0);
        } else if (r==zero) { // !NOT NEEDED!
            *r1=-a2/three;
            if (q<zero) { //imaginary case
                *r2=*r1;
                *r3=sqrt(-three*q);
                return(0);
            } else { //real roots
                //as we know q=/=0 we can simply set the roots as we need
                *r2=*r1;
                *r1=*r1+sqrt(three*q);
                *r3=*r1-sqrt(three*q);
                return(3);
            }
        } else if (q==zero & r==zero){
            *r1=beta;
            return(1);
        } else if (q*q*q==r*r) { // !NOT NEEDED!
            //implied that q>0
            *r1=-a2-two*(r/q + beta);
            *r2=r/q + beta;
            *r3=*r2;
            order_2(r1,r3);
            return(2);
        }

        alpha=cbrt(two*beta*beta*beta - a1*beta - a0); //can change to pow(z,1/3) if not using c11
        p=(three*beta*beta-a1)/(alpha*alpha);
        if (p==zero){yn=one;}
        else {
            if (p>11.0/three){y0=sqrt(p);} else if (p<-1.92) {y0=-1.0/p;} else {y0=1.0 + p/3.0 - (p*p*p)/81.0;} //set starting value of p
            yn=y0;
            /* printf("%g\n", yn_div); */
            for (count=1;count<4;count=count+1) {
                /* printf("count: %d\n", count); */
                yn_plus1 = yn - rcubic_value(zero,-p,-one,yn)/diffrcubic_value(zero,-p,-one,yn);
                /* printf("yn = %.10g, yn+1 = %.10g\n", yn,yn_plus1); */
                if (yn_plus1==yn) {/*printf("yn+1 == yn\n");*/break;}
                if (yn_div-fabs(yn-yn_plus1)<zero){/*printf("|yn+1 - yn| diverging\n");*/break;}
                yn_div=fabs(yn-yn_plus1);
                yn=yn_plus1;
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
    }
    printf("Error!\n");
    return(-1); //error
}
