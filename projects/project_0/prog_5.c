#include <stdio.h>
int main(void) {
	int high=160,step=2,F,C=-40;
	printf("     C          K         F          R\n");
	while(C <= high){
		F=32+9*C/5;
		printf("%6d %10.2f %9.1f %10.2f \n", C,C+273.15,(float)F,F+459.67);
		C=C+step;
	}
	return(0);
}