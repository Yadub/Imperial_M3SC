#include <stdio.h>
#include <math.h>

/* -Functions-needed-from-other-files----------------------------------------- */
int lin_root(double, double, double *);
int rcubic_roots(double, double, double, double *, double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, M3SC */
	print_statements();
	double  a2,a1,a0,r1,r2,r3;
    double alp=0.2135,bet=0.01709,P,R=0.0820578,V_ideal;
	int cubic_case,T;

    printf(" T,     P,   V_ideal,    V_vdw1,    V_vdw2,    V_vdw3\n");
    for (T=40;T<=50;T=T+5){
        for (P=1;P<=30;P=P+0.5){
            a2=-bet-R*T/P;
            a1=alp/P;
            a0=-(alp*bet)/P;

            lin_root(P,-R*T,&V_ideal);

            cubic_case = rcubic_roots(a2,a1,a0,&r1,&r2,&r3);
        	switch (cubic_case) {
        		case 0: printf("%d, %5.1f, %9.5f, %9.5f,\n",T,P,V_ideal,r1); break;
        		case 1: printf("%d, %5.1f, %9.5f, %9.5f,%9.5f,%9.5f, triple repeated roots\n",T,P,V_ideal,r1,r2,r3); break;
        		case 2: printf("%d, %5.1f, %9.5f, %9.5f,%9.5f,%9.5f, two roots repeated\n",T,P,V_ideal,r1,r2,r3); break;
                case 3: printf("%d, %5.1f, %9.5f, %9.5f, %9.5f, %9.5f\n",T,P,V_ideal,r1,r2,r3); break;
            }
        }
    }
}
/* --------------------------------------------------------------------------- */
