#include "random.h"
#include <stdio.h>

int main()
{
	srand(time(NULL));
	for (int i = 0; i < N; ++i)
		printf("%.5f\n", random01());
	for (int i = 0; i < N; ++i)
		printf("%.5f\n", random0n(20));
	for (int i = 0; i < N; ++i)
		printf("%d\n", tossOfOneDice());
	for (int i = 0; i < N; ++i)
		printf("%d\n", tossOfTwoDice());

	return 0;
}