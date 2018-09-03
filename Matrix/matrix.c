#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix newMatrix(int size) {
    Matrix m;
    m.size = size;
    m.data = (double**)calloc(size, sizeof(double*));
    for (int i = 0; i < size; i++) {
        m.data[i] = (double*)calloc(size, sizeof(double));
    }
    return m;
}

Matrix identity(int size) {
    Matrix identity = newMatrix(size);
    for(int i = 0; i < identity.size; i++) {
        identity.data[i][i] = 1;
    }
    return identity;
}

Matrix inverse(Matrix m) {
    Matrix temp = copy(m);
    Matrix inv = identity(temp.size);
    for(int i = 0; i < temp.size; i++) {
        double pivot = temp.data[i][i];
        if (pivot == 0 && !columnOfZeros(temp, i)) {
            for (int j = 0; j < temp.size; j++) {
                if (temp.data[j][i] != 0) {
                    temp = swapRows(temp, i, j);
                    inv = swapRows(inv, i, j);
                    break;
                }
            }
        }
        pivot = temp.data[i][i];
        for (int j = 0; j < temp.size; j++) {
            temp.data[i][j] /= pivot;
            inv.data[i][j] /= pivot;
        }

        for (int j = 0; j < temp.size; j++) {
            if (i == j) continue;
            double coef = temp.data[j][i];
            for (int k = 0; k < temp.size; k++) {
                temp.data[j][k] -= coef * temp.data[i][k];
                inv.data[j][k] -= coef * inv.data[i][k];
            }
        }
    }
    
    return inv;
}

Matrix swapRows(Matrix m, int row1, int row2) {
    for (int i = 0; i < m.size; i++) {
        double temp = m.data[row1][i];
        m.data[row1][i] = m.data[row2][i];
        m.data[row2][i] = temp;
    }
    return m;
}

Matrix mult(Matrix m1, Matrix m2) {
    Matrix res = newMatrix(m1.size);
    for (int i = 0; i < m1.size; i++) {
        for (int j = 0; j < m1.size; j++) {
            double sum = 0;
            for (int k = 0; k < m1.size; k++) {
                sum += m1.data[i][k] * m2.data[k][j];
            }
            res.data[i][j] = sum;
        }
    }
    return res;
}

int columnOfZeros(Matrix m, int col) {
    for (int i = 0; i < m.size; i++) {
        if (m.data[i][col] != 0) return 0;
    }
    return 1;
}

Matrix copy(Matrix m) {
    Matrix res = newMatrix(m.size);
    for (int i = 0; i < m.size; i++) {
        for (int j = 0; j < m.size; j++) {
            res.data[i][j] = m.data[i][j];
        }
    }
    return res;
}

void print(Matrix m) {
    for (int i = 0; i < m.size; i++) {
        for (int j = 0; j < m.size; j++) {
            printf("%.2lf\t", m.data[i][j]);
        }
        printf("\n");
    }
}