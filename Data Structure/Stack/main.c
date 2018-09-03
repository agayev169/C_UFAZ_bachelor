#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"

double plus(double x, double y) {return x+y;}
double minus(double x, double y) {return x-y;}
double mult(double x, double y) {return x*y;}
double Div(double x, double y) {return x/y;}
double Mod(double x, double y) {return (int)x%(int)y;}
double error() {
    fprintf(stderr,"ERROR! The only valid operators are + - * / %%\n");
    return 1;
}

double (*f[])()={plus, minus, mult, Div, Mod, error}; //Array of pointers on functions

int main(int argc, char const *argv[]) {
    // Lifo myCalcStack;
    double d = 0;
    char str[100], *p;

    int aF[256]; // array of functions
    for (int i = 0; i < 256; aF[i++] = 5);
    aF['+'] = 0; aF['-'] = 1; aF['x'] = 2; aF['*'] = 2; aF['/'] = 3; aF['%'] = 4;

    Lifo lifo;
    int n;

    // printf("Size of lifo: \n");
    // scanf("%d", &n);
    n = 100;
    constructLifo(&lifo, n);

    double num1, num2;

    while(1) {
        printf("Enter numbers or operators/q to break: ");
        scanf("%s", str);
        if (str[0] == 'q') break;
        d = strtod(str, &p);
        if (p != str)
            push(&lifo, d);
        else {
            if (str[0] == '+' || str[0] == '-' || str[0] == '*' ||
                str[0] == 'x' || str[0] == '/' || str[0] == '%') {
                    printf("Operator: %c\n", str[0]);
                    if (pop(&lifo, &num1) == 0 && pop(&lifo, &num2) == 0)
                        push(&lifo, (*f[aF[str[0]]])(num1, num2));
                    else push(&lifo, num1);
                    printTop(lifo);
            } else (*f[aF[str[0]]])();
        }
    }


    destructLifo(&lifo);

    return 0;
}
