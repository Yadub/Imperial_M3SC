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
	double  a[4],t[5],phi[5];

    double R = 6378137;
    double b = 6356752/R;
    double X = 4317364/R;
    double Y = 5461337/R;

	a[3] = 2.0*(X + 1.0 - b*b)/(b*Y);
    a[2] = 0;
	a[1] = 2.0*(X - 1.0 + b*b)/(b*Y);
    a[0] = -1.0;
	int quartic_case = rquartic_roots(a,t);
	printf("Quartic Case: %d\n", quartic_case);
    /*in degrees*/
    phi[1] = 2.0*atan(t[1]);
	phi[2] = 2.0*atan(t[2]);
	phi[3] = 2.0*atan(t[3]);
	phi[4] = 2.0*atan(t[4]);

	switch (quartic_case) {
		case 2:
		printf("       b,            t[1],          phi[1],            t[2],          phi[2],\n");
		printf("%8.6f, %15.6f, %15.6f, %15.6f, %15.6f,\n", b, t[1],phi[1],t[2],phi[2]);
		break;
		case 4:
		printf("       b,      t[1],      phi[1],      t[2],      phi[2],    t[3],    phi[3],    t[4],    phi[4],\n");
		printf("%8.6f, %15.6f, %15.6f, %15.6f, %15.6f, %15.6f, %15.6f, %15.6f, %15.6f\n", b, t[1],phi[1],t[2],phi[2],t[3],phi[3],t[4],phi[4]);
		break;
	}
	printf("\nCoordinate directly below the Satellite (rescaled to actual size)\n" );
	printf("X = %20.10g m, Y = %20.10g m\n\n", R*cos(phi[1]), R*b*sin(phi[1]));
	printf("Angle to Equator = %20.10g\n", atan(tan(phi[1])/b) *(180.0/M_PI));
	printf("Distance =      %20.10g m\n", R*sqrt( ( X-cos(phi[1]))*( X-cos(phi[1])) + ( Y-b*sin(phi[1]))*( Y-b*sin(phi[1])) ));
}
