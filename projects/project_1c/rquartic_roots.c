#include <float.h> //for DBL_EPSILON
#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
void order(double *, int);
int quad_roots(double *, double *);
int rcubic_roots(double *, double *);
/* -Functions-implemented-in-current-file------------------------------------- */
void swap(double *, int);
int squared_quadratic(double *, double *);
int return_roots(int, int, double *);
int rquartic_roots(double *, double *);
int quartic_roots_of_unity(double, double *);
/* --------------------------------------------------------------------------- */

int rquartic_roots(double *a, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    double zero=0;
    int qc1,qc2;

/* Optimization Cases that Skip the R-Quartic Method */
#ifndef NON_OPTIMIZED
    /* Part i */
    if (a[0]==zero){
        root[1] = 0;
        qc1 = rcubic_roots(a+1,root+1);
        return return_roots( root[1] == root [2] ? 1 : 2 , qc1 > 1 ? qc1 - 1 : qc1 , root);
    } /* Part iii */
    else if (a[3]==zero && a[2]==zero && a[1]==zero) {
        return quartic_roots_of_unity(-a[0], root);
    } /* Part ii */
    else if (a[3]==zero && a[1]==zero){
        return squared_quadratic(a, root);
    }
#endif

    double coefs_q1[3],coefs_q2[3];
    coefs_q1[2] = coefs_q2[2] = 1.0;

    double b[] = {4.0*a[0]*a[2] - a[1]*a[1] - a[0]*a[3]*a[3] , a[1]*a[3] - 4.0*a[0] , -a[2]};
    rcubic_roots(b,root);
    double r = root[1];

    //deal with underflow?
    double v0_coef = fabs(r) < fabs(a[0]) ? sqrt( (r/2.0)*(r/2.0) - a[0] ) : fabs(r/2.0)*sqrt( 1.0 - (4.0*a[0]/r)/r );
    double v1_coef = fabs(a[3]) < 1 ? sqrt(a[3]*a[3]/4.0 + r - a[2]) : fabs(a[3])*sqrt( 1.0/4.0 + (r/a[3])/a[3] - (a[2]/a[3])/a[3] );

#ifdef DEBUG
    printf("DEBUG REPORT| Not an Optimization Case\n");
    printf("DEBUG REPORT| r = %g\n", r);
    printf("DEBUG REPORT| v1_coef = %g, v0_coef = %g\n", v1_coef, v0_coef);
    printf("DEBUG REPORT| a[1] = %g, comparing val = %g, diff = %g\n", a[1], r*a[3]/2.0 , fabs(a[1]-r*a[3]/2.0));
#endif

    //if (fabs(a[1] - a1_comparison) < epsilon){
    if (a[1] < r*a[3]/2.0){
        coefs_q1[0] = r/2.0 + v0_coef , coefs_q1[1] = a[3]/2.0 + v1_coef;
        coefs_q2[0] = r/2.0 - v0_coef , coefs_q2[1] = a[3]/2.0 - v1_coef;
    } else {
        coefs_q1[0] = r/2.0 + v0_coef , coefs_q1[1] = a[3]/2.0 - v1_coef;
        coefs_q2[0] = r/2.0 - v0_coef , coefs_q2[1] = a[3]/2.0 + v1_coef;
    }

    qc1 = quad_roots(coefs_q1,root);
    qc2 = quad_roots(coefs_q2,root+2);
#ifdef DEBUG
    //printf("DEBUG REPORT| 2 coefs1 = %g %g %g\n", coefs_q1[0], coefs_q1[1], coefs_q1[2]);
    //printf("DEBUG REPORT| 2 coefs2 = %g %g %g\n", coefs_q2[0], coefs_q2[1], coefs_q2[2]);
    printf("DEBUG REPORT| qc1 = %d, qc2 = %d\n", qc1, qc2);
    printf("DEBUG REPORT| roots = %g %g %g %g\n", root[1], root[2], root[3], root[4]);
#endif
    return return_roots(qc1, qc2, root);
}

/* --------------------------------------------------------------------------- */
int return_roots(int q1, int q2, double * root){
    /* Bhageria, Yadu, 00733164, M3SC */
#ifdef DEBUG
    printf("DEBUG REPORT| return_roots() called\n");
#endif
    if (q1 == 0 && q2 == 0){
        if (root[1] < root[3]){
            swap(root,2);
        } return 0;
    } else if (q1 == 0){
        swap(root,2);
        order(root , 2);
        return 2;
    } else if (q2 == 0){
        order(root,2);
        return 2;
    } else if (q1 == 1){
        if (root[1] == root[3] || root[1] == root[4]){
            order(root,4);
            return 1;
        }
    } else if (q2 == 1){
        if (root[3] == root[1] || root[3] == root[2]){
            order(root,4);
            return 1;
        }
    }
#ifdef DEBUG
    printf("DEBUG REPORT| q1 = %d, q2 = %d\n", q1,q2);
#endif

    order (root,4);
    return q1+q2;
}
/* --------------------------------------------------------------------------- */
void swap(double *nums, int n){
    /* Bhageria, Yadu, 00733164, M3SC */
    double temp;
    int i;
#ifdef DEBUG_FULL
    printf("DEBUG REPORT| Roots before calling swap: %g %g %g %g\n",nums[1],nums[2],nums[3],nums[4]);
#endif
    for (i=1;i<n+1;i++){
        temp = nums[i];
        nums[i] = nums[n+i];
        nums[n+i] = temp;
    }
#ifdef DEBUG_FULL
    printf("DEBUG REPORT| Roots after calling swap: %g %g %g %g\n",nums[1],nums[2],nums[3],nums[4]);
#endif
}
/* --------------------------------------------------------------------------- */
int quartic_roots_of_unity(double r, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    if (r>0){
        root[1] = root[4] = sqrt(sqrt(r));
        root[2] = -root[1];
        root[3] = 0;
        return 2;
    }
    root[1] = root[2] = root[4] = sqrt(-sqrt(r)/2);
    root[3] = -root[1];
    return 0;
}
/* --------------------------------------------------------------------------- */
int squared_quadratic(double *a, double *root){
    /* Bhageria, Yadu, 00733164, M3SC */
    double b[3] = { a[0], a[2] , 1};
    double qroot[3];
    int q1, q2;

    int q = quad_roots(b,qroot);
    if (q == 0){
        root[1] = sqrt( (qroot[1] + sqrt(qroot[1]*qroot[1] + qroot[2]*qroot[2]) ) / 2.0 );
        root[3] = -root[1];
        root[2] = root[4] = sqrt( (qroot[1] - sqrt(qroot[1]*qroot[1] + qroot[2]*qroot[2]) ) / 2.0 );
        return 0;
    } else if (q == 1){
        b[0] = -qroot[1]; b[1] = 0; b[2] = 1;
        q1 = quad_roots(b,root);
        root[3] = root[1];
        root[4] = root[2];
        return (q1+q1);
    }
    b[0] = -qroot[1]; b[1] = 0; b[2] = 1;
    double c[] = {-qroot[2],0,1};

    q1 = quad_roots(b,root);
    q2 = quad_roots(c,root+2);
    return(q1+q2);
}
