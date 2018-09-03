#include <stdio.h>
#include <math.h>

int xa,ya,xb,yb;
double dist;

int main() {
	printf("Enter x1,y1,x2 and y2\n");
	scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
	dist = sqrt(pow((xb-xa),2)+pow((yb-ya),2));
	printf("The distance between A and B = %f\n",dist);
}
