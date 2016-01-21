#include <stdio.h>
int main(void) {
	double a1,a0;
	printf("enter coefficients of Linear Equation a1*x+a0=0\n");
	printf("in the order a1,a0, seperated by spaces\n");
	scanf("%lf %lf",&a1,&a0);
	if (a1==0){
		if (a0==0){
			printf("a1=a0=0 so the equation is true for all x\n");
		} else{
			printf("a1=0 and a0!=0 so the equation is contradictory\n");
		} return(0);
	} printf("The Solution is x = %.2f \n", -a0/a1);
	return(0);
}