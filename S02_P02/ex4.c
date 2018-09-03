#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Point;

void dist(Point pt1, Point pt2) {
	printf("Dist = %f\n", sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
}

void exchange(Point *pt1, Point *pt2) {
	float hold = pt1->x;
	pt1->x = pt2->x;
	pt2->x = hold;
	hold = pt1->y;
	pt1->y = pt2->y;
	pt2->y = hold;
}

void showstrct(Point pt) {
	printf("pt.x = %f\npt.y = %f\n", pt.x, pt.y);
}

int main() {
	Point point;
	Point point2;
	point.x = 3;
	point.y = 4;
	point2.x = 5;
	point2.y = 12;
	printf("point.x = %f\npoint.y = %f\npoint2.x = %f\npoint2.y = %f\n", point.x, point.y, point2.x, point2.y);
	exchange(&point, &point2);
	printf("\n");
	printf("point.x = %f\npoint.y = %f\npoint2.x = %f\npoint2.y = %f\n", point.x, point.y, point2.x, point2.y);
	
	showstrct(point);
	showstrct(point2);

	dist(point, point2);
}
