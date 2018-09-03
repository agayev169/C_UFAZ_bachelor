#include "stdio.h"

void setMap (int width, int height, int map2D[height][width], int obstacles[][2], int obstacles_num, int entrance[2], int exit[2]);
//void setMap1D(int map2D[][], int width, int height, int map1D[]);
int clamp(int n, int width, int height);
void setGraphs (int width, int height, int map2D[width][height], int graphs[][4]);
void findWay (int currentPos[2], int entrance[2], int graphs[][4], int const width, int const height, int map2D[width][height], int *result, int steps, int been[height][width]);

int main()
{
	int w, h;
	scanf("%d, %d", &w, &h);
	int const width = w;
	int const height = h;
	int map2D[height][width];

	int entrance[2];
	for (int i = 0; i < 2; i++) scanf("%d", &entrance[i]);

	int exit[2];
	for (int i = 0; i < 2; i++) scanf("%d", &exit[i]);

	int n;
	scanf("%d", &n);
	int obstacles[n][2];
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < 2; j++) 
			scanf("%d", &obstacles[i][j]);

	setMap(width, height, map2D, obstacles, n, entrance, exit); // Sets 1 where we can go, 0 where we cannot, enter as 2 and exit as 3 

	// map1D[width * height];
	// setMap1D(map2D, width, height, map1D);

	int graphs[width * height][4];
	setGraphs(width, height, map2D, graphs);

	int been[height][width];

	int result = -1;
	findWay(exit, entrance, graphs, width, height, map2D, &result, 0, been);

	printf("%d\n", result);

	return 0;
}


void setMap (int width, int height, int map2D[height][width], int obstacles[][2], int obstacles_num, int entrance[2], int exit[2]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < obstacles_num; k++) {
				if (obstacles[k][0] == j && obstacles[k][1] == i) map2D[i][j] = 0;
			}
			if (entrance[0] == j && entrance[1] == i) map2D[i][j] = 2;
			if (exit[0] == j && exit[1] == i) map2D[i][j] = 3;
		}
	}
}

// void setMap1D (int map2D[][], int width, int height, int map1D) {
// 	for (int i = 0; i < height; i++) {
// 		for (int j = 0; j < width; j++) {
// 			map1D[i*i + j] = map2D[j][i];
// 		}
// 	}
// }

int clamp (int n, int width, int height) {
	if (n >= width * height || n < 0) return -1;
	return n;
}

void setGraphs (int width, int height, int map2D[width][height], int graphs[][4]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (clamp(i-1, width, height) != -1) graphs[i*height + j][0] = map2D[i-1][j]; else graphs[i*height + j][0] = -1;
			if (clamp(i+1, width, height) != -1) graphs[i*height + j][1] = map2D[i+1][j]; else graphs[i*height + j][1] = -1;
			if (clamp(j-1, width, height) != -1) graphs[i*height + j][2] = map2D[i][j-1]; else graphs[i*height + j][2] = -1;
			if (clamp(j+1, width, height) != -1) graphs[i*height + j][3] = map2D[i][j+1]; else graphs[i*height + j][3] = -1;
		}
	}
}

void findWay (int currentPos[2], int entrance[2], int graphs[][4], int const width, int const height, int map2D[width][height], int *result, int steps, int been[height][width]) {
	if (been[currentPos[0]][currentPos[1]] != 0) return;
	++been[currentPos[0]][currentPos[1]];
	if (currentPos[0] == entrance[0] && currentPos[1] && entrance[1])
		if (*result != -1 && *result < steps) *result = steps;
	for (int i = 0; i < 4; i++) if (graphs[currentPos[1]*width+currentPos[0]][i] != -1) findWay (graphs[currentPos[1]*width+currentPos[0]][i], entrance[2], graphs[width*height][4], width, height, map2D, &result, steps, been[height][width]);
}