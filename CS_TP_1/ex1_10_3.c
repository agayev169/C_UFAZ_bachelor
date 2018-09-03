#include <stdio.h>
#include <math.h>

int a=4,b=21,c=3,d;
float x1,x2;

int main() {
	printf("Enter a,b and c\n");
	scanf("%d%d%d",&a,&b,&c);
	d = pow(b,2)-4*a*c;
	printf("a = %d,b = %d,c = %d,D = %d\n",a,b,c,d);
	if (d>0) {
		x1 = (-b + sqrt(d))/(2*a);
		printf("x1 = %f\n",x1);
		x2 = (-b - sqrt(d))/(2*a);
		printf("x2 = %f\n",x1);
	}
}
