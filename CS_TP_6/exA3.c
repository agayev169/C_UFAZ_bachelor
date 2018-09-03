#include <stdio.h>

int mystery2 (const char *s); /* Declaring function mystery2 */

int main() {
	char string[80]; /* Declaring array string[80] of chars */
	printf("Enter a string: ");
	scanf("%s", string);/* Scaning elements of array */
	printf("%d\n", mystery2(string)); /* Printing the result of function mystery2 */
	return 0;
}

int mystery2 (const char *s) {
	int i; /* Declaring counter i */
	for (i = 0; *s != '\0'; s++) /* Initialazin our counter; checking if element of array is space or new line; changing the address to the next element  */
		i++;
	return i; /* Returnin number of chars till space or new line */
}
