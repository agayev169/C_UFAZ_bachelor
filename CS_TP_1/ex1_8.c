#include <stdio.h>

int main() {
	if ((signed)sizeof(int)<-1) /* There was a problem sinc sizeof() returns unsingned number, but -1 is signed. Now this code works in a right way */
		printf("Bizzarre, bizzarre ...\n");
	else printf("Tout est normal\n");
}
