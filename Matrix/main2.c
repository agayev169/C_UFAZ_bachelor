#include <stdio.h>
#include <stdlib.h>

double **newMatrix(int size) { // Создание новой матрицы
    double **data;
    data = (double**) calloc(size, sizeof(double*));
    for (int i = 0; i < size; i++) {
        data[i] = (double*)calloc(size, sizeof(double));
    }
    return data;
}

double **identity(int size) { // Создание единично матрицы
    double **identity = newMatrix(size);
    for(int i = 0; i < size; i++) {
        identity[i][i] = 1;
    }
    return identity;
}

double **copy(double **data, int size) { // Создание копии матрицы
    double **res = newMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[i][j] = data[i][j];
        }
    }
    return res;
}

int columnOfZeros(double **data, int size, int col) { // Проверка того, есть ли ненуленвые элементы в данной колонне данной матрицы
    for (int i = 0; i < size; i++) {
        if (data[i][col] != 0) return 0;
    }
    return 1;
}

double **swapRows(double **data, int size, int row1, int row2) { // Обмен местами двух строк матрицы
    for (int i = 0; i < size; i++) {
        double temp = data[row1][i];
        data[row1][i] = data[row2][i];
        data[row2][i] = temp;
    }
    return data;
}

double **inverse(double **data, int size) { // Нахождение инверсии данной матрицы
    double **temp = copy(data, size); // Копирование матрцы, которая будет преобразована в обратную матрицу
    double **inv = identity(size); // Создание единичной матрицы
    for (int i = 0; i < size; i++) { // Цикл для использования алгоритма на всех строках
        double pivot = temp[i][i]; // Запоминаем "диагональный" элемент(пивот) данной строки
        if (pivot == 0 && !columnOfZeros(temp, size, i)) { // Если пивот равен нулю и в колонне не все элементы равны нулю
            for (int j = 0; j < size; j++) { // Цикл для нахождения ненулевого элемента в i-ой колонне
                if (temp[j][i] != 0) {
                    temp = swapRows(temp, size, i, j); // Замена двух строк в исходной матрице
                    inv = swapRows(inv, size, i, j); // Замена двух строк в единичной матрице
                    break; // Конец цикла
                }
            }
        }
        pivot = temp[i][i]; // Пивот равен новому элементу (Если в колонне был хотя бы один ненулевой элемент)
        for (int j = 0; j < size; j++) { // Делим все элементы в исходной и единичной матрице на пивот, чтобы получить 1 в элементе (i, i)
            temp[i][j] /= pivot; 
            inv[i][j] /= pivot;
        }

        for (int j = 0; j < size; j++) { // Приводим все элементы под пиовотом к нулю
            if (i == j) continue;
            double coef = temp[j][i];
            for (int k = 0; k < size; k++) {
                temp[j][k] -= coef * temp[i][k];
                inv[j][k] -= coef * inv[i][k];
            }
        }
    }
    
    return inv;
}

double **mult(double **m1, double **m2, int size) { // Умножение двух кввадратных матриц одинакового размера
    double **res = newMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double sum = 0;
            for (int k = 0; k < size; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}

void print(double **m, int size) { // Печатание матрицы
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.10lf\t", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size = 3;
    double **m = newMatrix(size);
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            m[i][j] = 1 / (double) (i + j + 1);
        }
    }
    double **inv = inverse(m, size);
    print(m, size);
    printf("\n");
    print(inv, size);
    printf("\n");
    print(mult(m, inv, size), size);


    return 0;
}