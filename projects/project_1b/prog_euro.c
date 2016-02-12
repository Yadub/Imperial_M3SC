#include <stdio.h>
int main(void){
	printf("Euro : \xE2\x82\xAC"); //Check if this works in Windows
	printf("\nEuro : \u20AC"); //Another way to represent the Euro sign
	printf("\n");
}