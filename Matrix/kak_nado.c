#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
double kv(double a)
{
    double w;
    w = 1;
    for (int i = 0; i < 2; i++)
    {
        w = w * a;
    }
    return w;
}
void f(double **a, double **e, int n)
{
    double m, w;
    m = 0.0;
    double o, u, p;
    int m3;
    for (int j = 0; j < n; j++)
    {
        for (int i = j; i < n; i++)
        {
            if (fabs(a[i][j]) > m)
            {
                m = a[i][j];
                m3 = i;
            }
        }
        for (int y = 0; y < n; y++)
        {
            w = e[m3][y];
            e[m3][y] = e[j][y];
            e[j][y] = w;

            w = a[m3][y];
            a[m3][y] = a[j][y];
            a[j][y] = w;
        }
        p = a[j][j];
        for (int g = 0; g < n; g++)
        {
            e[j][g] = e[j][g] / p;
            a[j][g] = a[j][g] / p;
        }

        for (int d = j + 1; d < n; d++)
        {
            o = a[d][j];
            for (int g = 0; g < n; g++)
            {
                e[d][g] = e[d][g] - o * e[j][g];
                a[d][g] = a[d][g] - o * a[j][g];
            }
        }
        m = 0;
    }
    for (int j = 0; j < n; j++)
    {
        for (int d = 0; d < j; d++)
        {
            u = a[d][j];
            for (int g = 0; g < n; g++)
            {
                e[d][g] = e[d][g] - u * e[j][g];
                a[d][g] = a[d][g] - u * a[j][g];
            }
        }
    }
    return;
}
void gilb_yed(double **a, int n)
{
    double t[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            t[i][j] = 1 + i + j;
            a[i][j] = 1 / t[i][j];
            if (i == j)
            {
                a[i][j] = a[i][j] + 1;
            }
        }
    }
    return;
}
void yed(double **e, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                e[i][j] = 1;
            else
                e[i][j] = 0;
        }
    }
    return;
}
void polc(double **c, double **e, double **g, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int y = 0; y < n; y++)
            {
                c[i][j] = c[i][j] + g[i][y] * e[y][j];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                c[i][i] = c[i][i] - 1;
        }
    }
    return;
}

double normi1(double **c, int n)
{
    double norm;
    norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(c[i][j]) > norm)
            {
                norm = fabs(c[i][j]);
            }
        }
    }
    return norm;
}
double normi2(double **c, int n)
{
    double norm;
    norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            norm = norm + fabs(c[i][j]);
        }
    }
    return norm;
}
double normi3(double **c, int n)
{
    double norm, b, w, s;
    s = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b = c[i][j];
            w = kv(b);
            s = s + w;
        }
    }
    norm = sqrt(s);
    return norm;
}
int main(void)
{
    double **a1;           // исходная матрица.
    double **e1;           // единичная, что станет позже обратной.
    double **c1;           // норма матрицы а.
    double **g1;           // исходная const
    double t1, n1, n2, n3; // Нормы.
    int n;                 // Ранг матрицы.
    printf(" Введите размерность матрицы: ");
    scanf("%d", &n);
    a1 = (double **)malloc(n * sizeof(double *));
    e1 = (double **)malloc(n * sizeof(double *));
    c1 = (double **)malloc(n * sizeof(double *));
    g1 = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        g1[i] = (double *)malloc(n * sizeof(double));
        e1[i] = (double *)malloc(n * sizeof(double));
        c1[i] = (double *)malloc(n * sizeof(double));
        a1[i] = (double *)malloc(n * sizeof(double));
    }
    t1 = clock();
    gilb_yed(a1, n);
    yed(e1, n);
    gilb_yed(g1, n);
    f(a1, e1, n);
    polc(c1, e1, g1, n);
    n1 = normi1(c1, n);
    n2 = normi2(c1, n);
    n3 = normi3(c1, n);
    t1 = clock() - t1;
    t1 /= CLOCKS_PER_SEC;
    printf("2-oy test:");
    printf("\n");
    printf("Max modula raznosti: %le", n1);
    printf("\n");
    printf("Summa moduley: %le", n2);
    printf("\n");
    printf("Koren summi kvadratov: %le", n3);
    printf("\n\n");
    printf("%le vremeni", t1);
    return 0;
}
