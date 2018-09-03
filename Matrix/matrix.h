#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct {
    double **data;
    int size;
} Matrix;

Matrix newMatrix(int size);
Matrix inverse(Matrix m);
Matrix identity(int size);
Matrix swapRows(Matrix m, int row1, int row2);
Matrix mult(Matrix m1, Matrix m2);
int columnOfZeros(Matrix m, int col);
Matrix copy(Matrix m);
void print(Matrix m);


#endif