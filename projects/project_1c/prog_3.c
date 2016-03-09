#include <stdio.h>
#include <math.h>

#ifndef M_PI /*incase Pi is not defined on a compiler */
#    define M_PI 3.14159265358979323846
#endif

/* -Functions-needed-from-other-files----------------------------------------- */
int rquartic_roots(double *, double *);
void print_statements(); //contained in the quad_roots.c file
/* --------------------------------------------------------------------------- */

int main(void) {
	/* Bhageria, Yadu, 00733164, M3SC */
	print_statements();
	double  a[4],t[5],phi[5],X=3.0/8.0,Y=1.0/2.0,b;
	int quartic_case;

	a[2] = 0;
	a[0] = -1.0;
	printf("    b ,  case ,      t[1] ,      t[2] ,      t[3] ,      t[4] ,    phi[1] ,    phi[2] ,    phi[3] ,    phi[4]\n");

    for (b=0.05; b<1; b=b+0.05){
		a[3] = 2.0*(X + 1.0 - b*b)/(b*Y);
		a[1] = 2.0*(X - 1.0 + b*b)/(b*Y);

		quartic_case = rquartic_roots(a,t);

		//in degrees
		phi[1] = 2.0*atan(t[1]) * (180.0/M_PI);;
		phi[2] = 2.0*atan(t[2]) * (180.0/M_PI);;
		phi[3] = 2.0*atan(t[3]) * (180.0/M_PI);;
		phi[4] = 2.0*atan(t[4]) * (180.0/M_PI);;

		switch (quartic_case) {
			case 0: printf("%5.2f\n", b); break;
			case 1: printf("%5.2f , %5d , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f\n", b, quartic_case, t[1],t[2],t[3],t[4],phi[1],phi[2],phi[3],phi[4]); break;
			case 2: printf("%5.2f , %5d , %9.4f , %9.4f ,           ,           , %9.4f , %9.4f ,\n", b, quartic_case, t[1],t[2],phi[1],phi[2]); break;
			case 3: printf("%5.2f , %5d , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f\n", b, quartic_case, t[1],t[2],t[3],t[4],phi[1],phi[2],phi[3],phi[4]); break;
			case 4: printf("%5.2f , %5d , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f , %9.4f\n", b, quartic_case, t[1],t[2],t[3],t[4],phi[1],phi[2],phi[3],phi[4]); break;
		}
	}
}
