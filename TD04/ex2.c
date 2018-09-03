#include <stdio.h>

int divide (float a, float b, float *q);
//int firstDegreeEquation (float a, float b, float *solution);

int main()
{
	float q;
	int res = divide (365, 5, *q);
	printf("%f\n", q);
	//res = firstDegreeEquation (1, 5);

	return 0;
}

int divide (float a, float b, float *q) {
	if (b == 0)
		return 0;
	*q = a/b;
	printf("%f\n", *q);
	return 1;
}

// int firstDegreeEquation (float a, float b, float *solution) {
// 	if (a == 0)
// 		return 0;
// 	*solution = -b/a;
	
// 	return 1;
// }