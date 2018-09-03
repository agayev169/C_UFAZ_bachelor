#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void identity(int size, double **identity) // Создание единичной матрицы
{
	int i;
	for (i = 0; i < size; i++)
	{
		identity[i][i] = 1;
	}
}

void gilbert(int size, double **m) //Матрица Гильберта
{
	int i, j;
	double t[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			t[i][j] = 1 + i + j;
			m[i][j] = 1 / t[i][j];
		}
	}
	return;
}

void copy(double **data, int size, double **res) // Создание копии матрицы
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			res[i][j] = data[i][j];
		}
	}
}

int findMaxInColumn(double **m, int size, int col) {
	double maximum = fabs(m[0][col]);
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (maximum < fabs(m[i][col])) {
			maximum = fabs(m[i][col]);
			index = i;
		}
	}
	return index;
}

void swapLines(double **m, int size, int r1, int r2) {
	for (int i = 0; i < size; i++) {
		double temp = m[r1][i];
		m[r1][i] = m[r2][i];
		m[r1][i] = temp;
	}
}

void print(double **m, int size) // Печатание матрицы
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%le\t", m[i][j]);
		}
		printf("\n");
	}
}

double **inverse(double **m, double **ed, int size) // Нахождение инверсии данной матрицы
{
	double **temp = (double**) malloc((size) * sizeof(double*));
	for (int i = 0; i < size; i++) {
		temp[i] = (double*) malloc((size) * sizeof(double));
	}
	copy(m, size, temp);
	int toSwap = findMaxInColumn(temp, size, 0);
	if (toSwap != 0) {
		swapLines(temp, size, 0, toSwap);
	}

	double pivot = temp[0][0];
	for (int i = 0; i < size; i++) {
        temp[i][0] /= pivot;
        ed[i][0] /= pivot;
    }

	for (int i = 1; i < size; i++) {
		double coef = temp[i][0];
		for (int j = 0; j < size; j++) {
			temp[i][j] -= coef * temp[0][j];
			ed[i][j] -= coef * ed[0][j];
		}
	}

	printf("Size: %d\n", size);
	print(temp, size);
	printf("\n");

	if (size == 1) return ed;

	double **temp2 = (double**) malloc((size - 1) * sizeof(double*));
	for (int i = 0; i < size - 1; i++) {
		temp2[i] = (double*) malloc((size - 1) * sizeof(double));
		for (int j = 0; j < size - 1; j++) {
			temp2[i][j] = temp[i + 1][j + 1];
		}
	}

	double **ed2 = (double**) malloc((size - 1) * sizeof(double*));
	for (int i = 0; i < size - 1; i++) {
		ed2[i] = (double*) malloc((size - 1) * sizeof(double));
		for (int j = 0; j < size - 1; j++) {
			ed2[i][j] = ed[i + 1][j + 1];
		}
	}

	ed2 = inverse(temp2, ed2, size - 1);

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			ed[i + 1][j + 1] = ed2[i][j];
		}
	}



	return ed;
	



	// int i, j, k;
	// double maximum, coef, con;
	// copy(data, size, temp); // Копирование матрицы, которая будет преобразована в обратную матрицу
	// identity(size, ed);		// Создание единичной матрицы
	// maximum = fabs(temp[0][0]);
	// for (i = 0; i < size; i++)
	// {
	// 	j = 0;
	// 	if (temp[i][j] > maximum)
	// 	{
	// 		maximum = fabs(temp[i][j]);
	// 		k = i;
	// 	}
	// }
	// for (i = 0; i < size; i++)
	// {
	// 	con = temp[i][k];
	// 	temp[i][k] = temp[i][k];
	// 	temp[i][k] = con;

	// 	con = ed[i][k];
	// 	ed[i][k] = ed[i][k];
	// 	ed[i][k] = con;
	// }
}

void mult(double **m1, double **m2, int size, double **res) // Умножение двух кввадратных матриц одинакового размера
{
	int i, j, k;
	double sum;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			sum = 0;
			for (k = 0; k < size; k++)
			{
				sum += m1[i][k] * m2[k][j];
			}
			res[i][j] = sum;
		}
	}
}

void matrix_identity(double **multiplic, int size) //Отнимаю от произведения двух матриц(исходная и обратная) единичную
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == j)
			{
				multiplic[i][j] = multiplic[i][j] - 1;
			}
		}
	}
	return;
}

double maximum_mod(double **multiplic, int size) //Первая норма: максимальный модуль
{
	int i, j;
	double maximum;
	maximum = fabs(multiplic[0][0]);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (fabs(multiplic[i][j]) > maximum)
			{
				maximum = fabs(multiplic[i][j]);
			}
		}
	}
	return maximum;
}

double sum_mod(double **multiplic, int size) //Вторая норма: сумма модулей каждого элемента
{
	int i, j;
	double sum;
	sum = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			sum = sum + fabs(multiplic[i][j]);
		}
	}
	return sum;
}

double norma(double **multiplic, int size) //Третья норма: сумма квадратов модулей каждого элемента под корнем
{
	int i, j;
	double sum, norm;
	sum = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			sum = sum + fabs(multiplic[i][j]) * fabs(multiplic[i][j]);
		}
	}
	norm = sqrt(sum);
	return norm;
}

int main()
{
	// int size, i;
	// printf("Enter the size of matrix: ");
	// scanf("%d", &size);
	// double **m = NULL, **ed, tim, **multiplic, **temp, maxi, summa, norm;

	// multiplic = (double **)malloc(size * sizeof(double *));
	// m = (double **)malloc(size * sizeof(double *));
	// temp = (double **)malloc(size * sizeof(double *));
	// ed = (double **)malloc(size * sizeof(double *));

	// for (i = 0; i < size; i++)
	// {
	// 	m[i] = (double *)malloc(size * sizeof(double));
	// 	multiplic[i] = (double *)malloc(size * sizeof(double));
	// 	temp[i] = (double *)malloc(size * sizeof(double));
	// 	ed[i] = (double *)malloc(size * sizeof(double));
	// }

	// tim = clock();

	// gilbert(size, m);

	// ed = inverse(temp, ed, m, size);
	/* print(temp, size);
    printf("\n Matrix: \n\n");
    print(m, size);
    printf("\n\n Inversion: \n\n");
    print(inv, size);
    printf("\n\n Multiplication: \n\n");
    print(multiplic, size);*/
	// mult(m, inv, size, multiplic);
	// matrix_identity(multiplic, size);
	// printf("\nMatrix for check:\n\n");
	// print(multiplic, size);

	// maxi = maximum_mod(multiplic, size);
	// printf("\nMaximum of modules: %le\n", maxi);
	// summa = sum_mod(multiplic, size);
	// printf("\nSum of modules: %le\n", summa);
	// norm = norma(multiplic, size);
	// printf("\nNorma: %le\n", norm);

	// tim = clock() - tim;
	// tim /= CLOCKS_PER_SEC;
	// printf("\n\nTotal full time= %lf \n", tim);

	int size = 3;
	double **m = (double**) malloc(size * sizeof(double*));
	for (int i = 0; i < size; i++) {
		m[i] = (double*) malloc(size * sizeof(double));
	}
	gilbert(size, m);
	print(m, size);

	double **ed = (double**) malloc(size * sizeof(double*));
	for (int i = 0; i < size; i++) {
		ed[i] = (double*) malloc(size * sizeof(double));
		for (int j = 0; j < size; j++) {
			if (i == j) ed[i][j] = 1;
			else ed[i][j] = 0;
		}
	}
	print(inverse(m, ed, size), size);

	return 0;
}
