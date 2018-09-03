#include <stdio.h>

void useLocal();
void useStaticLocal();
void useGlobal();

int x = 1; /*Global variable*/

int main() {
	int x = 5; /*Local variable in main function*/

	printf("Local x in outer scope of main is %d\n", x);  /*5*/
	
	{
		int x = 7; /*Local variable in new scope*/

		printf("Local x in inner scope of main is %d\n", x); /*7*/
	}
	printf("Local x in outer scope of main is %d\n", x);
	
	useLocal();
	useStaticLocal();
	useGlobal();
	useLocal();
	useStaticLocal();
	useGlobal();

	printf( "\n Local x in main is %d\n", x);
	return 0;
}

void useLocal() {
	int x = 25;

	printf("\nLocal x in useLocal is %d after entering useLocal\n", x);
	x++;
	printf("Local x in useLocal is %d on exiting useStaticLocal\n", x);
}

void useStaticLocal() {
	static int x = 50;
	
	printf("\nLocal static x is %d on entering useStaticLocal\n", x);
	x++;
	printf("\nLocal static x is %d on exiting useStaticLocal\n", x);
}

void useGlobal() {
	printf("\nGlobal x is %d on entering useGlobal\n", x);
	x *= 10;
	printf("\nGlobal x is %d on exiting useGlobal\n", x);
}
