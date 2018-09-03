#include <stdio.h>

int belongs (int searched, int my_array[], int nb_elements);

int main()
{
	int my_array[] = {0, 1, 2, 3, 4};
	printf("%d\n", belongs(6, my_array, 5));

	return 0;
}

int belongs (int searched, int my_array[], int nb_elements) {
	if (nb_elements == 0) return 0;
	if (my_array[0] == searched) return 1;
	return belongs(searched, my_array+1, nb_elements-1);
}