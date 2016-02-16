#include <stdio.h>
#include <math.h>
#include "order_nums.h"
#include "lin_root.h"
#include "quad_roots.h"
#include "rcubic_roots_optimized.h"
#include "print_statements.h"

/* This version of the code deals with the case where
a1^2 >> 4 a0 a2 or 4 a0 a2 >> a1^2 */

int main(void) {
	print_statements();
	double  a2,a1,a0,r1,r2,r3;
    double alp=0.2135,bet=0.01709,P,R=0.0820578,V_ideal;
	int cubic_case,T;

    printf(" T,     P,        V_ideal, V that satisfy the Van Der Waals cubic equation\n");
    for (T=40;T<=50;T=T+5){
        for (P=1;P<=30;P=P+0.5){
            a2=-bet-R*T/P;
            a1=alp/P;
            a0=-(alp*bet)/P;

            lin_root(P,-R*T,&V_ideal);

            cubic_case = rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
        	switch (cubic_case) {
        		case 0: printf("%d, %5.10g, %14.10f, %14.10f\n",T,P,V_ideal,r1); break;
        		case 1: printf("There are triple repeated real roots.\n r1 = r2 = r3 = %.10g \n", r1); break;
        		case 2: printf("There is a pair of repeated real roots.\n r1 = %.10g, r2 = %.10g, r3 = %.10g \n", r1,r2,r3); break;
                case 3: printf("%d, %5.10g, %14.10f, %14.10f, %14.10f, %14.10f\n",T,P,V_ideal,r1,r2,r3); break;
            }
        }
    }
}
