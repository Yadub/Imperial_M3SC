#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* -Functions-needed-from-other-files----------------------------------------- */
void print_vector(double *, int);
double *SFactors(int);
/* --------------------------------------------------------------------------- */
int main(void){
    int N;

    printf("Enter N: ");
    scanf("%d", &N);
    printf("\n");
    
    double * test_factors = SFactors(N);
    print_vector(test_factors, N/2);
}
/* --------------------------------------------------------------------------- */
