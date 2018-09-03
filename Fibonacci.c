#include <stdio.h>

int n;

int main() {
	printf("Which element of Fibonacci sequence you want me to calculate? ");
	scanf("%d",&n);
	int arr[n];
	arr[0]=0;
	arr[1]=1;
	for (int i=2;i<n+1;i++) 
		arr[i] = arr[i-1] + arr[i-2];
	printf("%d\n",arr[n]);
}
