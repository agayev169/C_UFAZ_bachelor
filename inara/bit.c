#include <stdio.h>

unsigned char M[8] = {1, 2, 4, 8, 16, 32, 64, 128};

void showBits(unsigned char x);
int numOfZeros(unsigned char x);
void copyToArray(unsigned char x[], unsigned char X);
void zerosOnEvenBits(unsigned char x[]);
void zerosOnOddBits(unsigned char x[]);
unsigned char copyToChar(unsigned char x[]);

int main() {
//0
	int X, Y;
	scanf(" %d %d", &X, &Y);
//1
	showBits(X);
	showBits(Y);
//2
	printf("number of zeros of X = %d\n", numOfZeros(X));
	printf("number of zeros of Y = %d\n", numOfZeros(Y));
//3
	unsigned char x[8] = {0};
	unsigned char y[8] = {0};
	copyToArray(x, X);
//4
	zerosOnEvenBits(x);
	zerosOnOddBits(y);
//5
	x[5] = x[1] | x[3];//Неправильно
	x[7] = x[1] & x[3];
//6
	y[5] = y[1] | y[3];
	y[7] = y[1] & y[3];
//7
	X = copyToChar(x);
	Y = copyToChar(y);
	showBits(X);
	showBits(Y);

	return 0;
}

void showBits(unsigned char x) {
	for (int i = 7; i >= 0; --i)
		printf(x&M[i] ? "1" : "0");
	printf("\n");
}

int numOfZeros(unsigned char x) {
	int zeros = 0;//Название не соответствует значению!
	for (int i = 7; i >= 0; --i) {
		if (x&M[i]) zeros++;//Здесь почему-то не получается записать == 0, так что пришлось сделать так
	}
	return 8 - zeros;
}

void copyToArray(unsigned char x[], unsigned char X) {
	for (int i = 7; i >= 0; --i)
		x[i] = (X&M[i])/M[i];
}

void zerosOnEvenBits(unsigned char x[]) {
	for (int i = 0; i < 8; i+=2) x[i] = 0;
}

void zerosOnOddBits(unsigned char x[]) {
	for (int i = 1; i < 8; i+=2) x[i] = 1;
}

unsigned char copyToChar(unsigned char x[]) {
	unsigned char X = 0;
	for (int i = 7; i >= 0; --i)
		X+=M[i]*x[i];
	return X;
}