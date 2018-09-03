#include <stdio.h>
#include <math.h>

float height,time;

int main() {
	printf("Write the height(in meters) at which the body is located and I'll find the time of it's falling\n");
	scanf("%f",&height);
	time = sqrt(2 * height / 9.8);
	printf("The time of falling of the body that is located at %f meters above the ground = %.2f seconds\n",height,time);
}
