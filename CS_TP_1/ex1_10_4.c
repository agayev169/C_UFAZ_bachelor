#include <stdio.h>
#include <math.h>

int a=4,b=21,c=3,d;

int main() {
	printf("Enter a,b and c\n");
	scanf("%d%d%d",&a,&b,&c);
	d = pow(b,2)-4*a*c;
	printf("a = %d,b = %d,c = %d,D = %d\n",a,b,c,d);
	if (d>0) {
		float x1,x2;
		x1 = (-b + sqrt(d))/(2*a);
		printf("x1 = %.2f\n",x1);
		x2 = (-b - sqrt(d))/(2*a);
		printf("x2 = %.2f\n",x1);
	}
	else if (d==0) {
		float x1;
		x1 = (-b)/(2*a);
		printf("x = %.2f\n",x1);
	}
	else {
		float real = (-b)/(2*a);
		float imaginary = (sqrt(-d))/(2*a);
		printf("x1 = %.2f*i + %.2f\n",imaginary,real);
		printf("x2 = %.2f*i - %.2f\n",imaginary,real);
		printf("Imaginary part = %.2f, real part = %.2f\n",imaginary,real);
	}
}
