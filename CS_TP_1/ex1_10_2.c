#include <stdio.h>
#include <math.h>

int a=4,b=21,c=3,d;

int main() {
	printf("Enter a,b and c\n");
	scanf("%d%d%d",&a,&b,&c);
	d = pow(b,2)-4*a*c;
	printf("a = %d,b = %d,c = %d,D = %d\n",a,b,c,d);
}
