#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

typedef struct 
{
	int x, y;
} vector2;

int perRect(vector2 arr[], int n);
int perShape(vector2 arr[], int n);

int main()
{
	freopen("intel.in", "rt", stdin);
	freopen("intel.out", "wt", stdout);
	int n;
	cin >> n;
	vector2 arr[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i].x;
		cin >> arr[i].y;
	}
	int pr = perRect(arr, n);
	int ps = perShape(arr, n);

	cout << ps - pr;

	return 0;
}

int perRect(vector2 arr[], int n) {
	int minx = arr[0].x;
	int maxx = arr[0].x;
	int miny = arr[0].y;
	int maxy = arr[0].y;
	for (int i = 0; i < n; ++i)
	{
		if (minx > arr[i].x) minx = arr[i].x;  
		else if (maxx < arr[i].x) maxx = arr[i].x;
		if (miny > arr[i].y) miny = arr[i].y;
		else if (maxy < arr[i].y) maxy = arr[i].y;
	}
	return (maxx - minx + maxy - miny)*2;
}

int perShape(vector2 arr[], int n) {
	int res = (arr[0].x - arr[n-1].x + arr[0].y - arr[n-1].y) > 0 ? arr[0].x - arr[n-1].x + arr[0].y - arr[n-1].y : arr[n-1].x - arr[0].x + arr[n-1].y - arr[0].y;
	for (int i = 1; i < n; ++i)
	{
		res += arr[i-1].x > arr[i].x ? arr[i-1].x - arr[i].x : arr[i].x - arr[i-1].x;
		res += arr[i-1].y > arr[i].y ? arr[i-1].y - arr[i].y : arr[i].y - arr[i-1].y;
	}
	return res;
}