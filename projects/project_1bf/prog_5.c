#include <stdio.h>
int main(void) {
	/* Bhageria, Yadu, M3SC */
	printf("\n What is this? : \234");
	printf("\n Time          : %s ",__TIME__);
	printf("\n Date          : %s ",__DATE__);
	printf("\n Euro          : \xE2\x82\xAC"); //Check if this works in Windows
	printf("\n Euro          : \u20AC");
	printf("\n \n");
	return(0);
}
