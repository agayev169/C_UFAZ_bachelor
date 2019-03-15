#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

double plus(double x, double y) {return x + y;}
double minus(double x, double y) {return x - y;}
double mult(double x, double y) {return x * y;}
double div_(double x, double y) {return (y != 0) ? x / y : 0;}
double mod(double x, double y) {return (int) x % (int) y;}
double error() {
    fprintf(stderr,"Error! The only valid operators are +, -, *, / and %%\n");
    return 1;
}

double (*f[])()={plus, minus, mult, div_, mod, error};

int init() {return 0;}
int clean() {return 0;}

void push_test1() {
    int n = 10;

    Lifo lifo;
    constructLifo(&lifo, n);

    for (int i = 0; i < n; i++) {
        push(&lifo, i);
    }

    destructLifo(&lifo);
    CU_ASSERT(lifo.top == n);
}

void push_test2() {
    int n = 10;

    Lifo lifo;
    constructLifo(&lifo, n);

    for (int i = 0; i < n + 1; i++) {
        push(&lifo, i);
    }

    destructLifo(&lifo);
    CU_ASSERT(lifo.top == n);
}

void pop_test1() {
    int n = 10;

    Lifo lifo;
    constructLifo(&lifo, n);

    for (int i = 0; i < n; i++) {
        push(&lifo, i);
    }

    double num;
    for (int i = 0; i < n; i++) {
        pop(&lifo, &num);
    }

    destructLifo(&lifo);
    CU_ASSERT(lifo.top == 0);
}

void pop_test2() {
    int n = 10;

    Lifo lifo;
    constructLifo(&lifo, n);

    for (int i = 0; i < n; i++) {
        push(&lifo, i);
    }

    double num;
    for (int i = 0; i < n + 1; i++) {
        pop(&lifo, &num);
    }

    destructLifo(&lifo);
    CU_ASSERT(lifo.top == 0);
}

void sum_test() {
    double result = 0;

    int aF[256]; // array of functions
    for (int i = 0; i < 256; aF[i++] = 5);
    aF['+'] = 0; aF['-'] = 1; aF['x'] = 2; aF['*'] = 2; aF['/'] = 3; aF['%'] = 4;

    Lifo lifo;
    constructLifo(&lifo, 10);

    char *p;
    char str[100];
    double num1, num2;
    push(&lifo, 1);
    push(&lifo, 3);
    for (int i = 4; i < 11; ++i) {
        if (i % 2 != 0) {
            str[0] = '0' + i;
        } else {
            str[0] = '+';
        }
        double d = strtod(str, &p);
        if (p != str)
            push(&lifo, d);
        else {
            if (str[0] == '+' || str[0] == '-' || str[0] == '*' ||
                str[0] == 'x' || str[0] == '/' || str[0] == '%') {
                    if (pop(&lifo, &num2) == 0 && pop(&lifo, &num1) == 0)
                        push(&lifo, (*f[aF[(int) str[0]]])(num1, num2));
                    else push(&lifo, num2);
                    result = top(lifo);
            } else (*f[aF[(int) str[0]]])();
        }
    }

    destructLifo(&lifo);

    CU_ASSERT(result == 25);
}

void sub_test() {
    double result = 0;

    int aF[256]; // array of functions
    for (int i = 0; i < 256; aF[i++] = 5);
    aF['+'] = 0; aF['-'] = 1; aF['x'] = 2; aF['*'] = 2; aF['/'] = 3; aF['%'] = 4;

    Lifo lifo;
    constructLifo(&lifo, 10);

    char *p;
    char str[100];
    double num1, num2;
    push(&lifo, 9);
    push(&lifo, 7);
    for (int i = 6; i >= 0; --i) {
        if (i % 2 != 0) {
            str[0] = '0' + i;
        } else {
            str[0] = '-';
        }
        double d = strtod(str, &p);
        if (p != str)
            push(&lifo, d);
        else {
            if (str[0] == '+' || str[0] == '-' || str[0] == '*' ||
                str[0] == 'x' || str[0] == '/' || str[0] == '%') {
                    if (pop(&lifo, &num2) == 0 && pop(&lifo, &num1) == 0)
                        push(&lifo, (*f[aF[(int) str[0]]])(num1, num2));
                    else push(&lifo, num2);
                    result = top(lifo);
            } else (*f[aF[(int) str[0]]])();
        }
    }

    destructLifo(&lifo);

    CU_ASSERT(result == -7);
}



void mult_test() {
    double result = 0;

    int aF[256]; // array of functions
    for (int i = 0; i < 256; aF[i++] = 5);
    aF['+'] = 0; aF['-'] = 1; aF['x'] = 2; aF['*'] = 2; aF['/'] = 3; aF['%'] = 4;

    Lifo lifo;
    constructLifo(&lifo, 10);

    char *p;
    char str[100];
    double num1, num2;
    push(&lifo, 1);
    push(&lifo, 3);
    for (int i = 4; i < 11; ++i) {
        if (i % 2 != 0) {
            str[0] = '0' + i;
        } else {
            str[0] = '*';
        }
        double d = strtod(str, &p);
        if (p != str)
            push(&lifo, d);
        else {
            if (str[0] == '+' || str[0] == '-' || str[0] == '*' ||
                str[0] == 'x' || str[0] == '/' || str[0] == '%') {
                    if (pop(&lifo, &num2) == 0 && pop(&lifo, &num1) == 0)
                        push(&lifo, (*f[aF[(int) str[0]]])(num1, num2));
                    else push(&lifo, num2);
                    result = top(lifo);
            } else (*f[aF[(int) str[0]]])();
        }
    }

    destructLifo(&lifo);

    CU_ASSERT(result == 945);
}

void div_test1() {
    CU_ASSERT(div_(0, 0) == 0);
    CU_ASSERT(div_(1, 0) == 0);
    CU_ASSERT(div_(2, 0) == 0);
    CU_ASSERT(div_(3, 0) == 0);
}

void div_test2() {
    CU_ASSERT(div_(22, 7) == 22 / 7.0);
    CU_ASSERT(div_(23, 7) == 23 / 7.0);
    CU_ASSERT(div_(4, 15) == 4 / 15.0);
    CU_ASSERT(div_(1, 8) == 1 / 8.0);
}

void mod_test() {
    CU_ASSERT(mod(9, 5) == 4);
    CU_ASSERT(mod(9, 4) == 1);
    CU_ASSERT(mod(9, 3) == 0);
    CU_ASSERT(mod(9, 2) == 1);
}

int main(int argc, char const *argv[]) {
    /*
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
        scanf("%99s", str);
        if (str[0] == 'q') break;
        d = strtod(str, &p);
        if (p != str)
            push(&lifo, d);
        else {
            if (str[0] == '+' || str[0] == '-' || str[0] == '*' ||
                str[0] == 'x' || str[0] == '/' || str[0] == '%') {
                    printf("Operator: %c\n", str[0]);
                    if (pop(&lifo, &num2) == 0 && pop(&lifo, &num1) == 0)
                        push(&lifo, (*f[aF[(int) str[0]]])(num1, num2));
                    else push(&lifo, num2);
            } else (*f[aF[(int) str[0]]])();
        }
    }
    destructLifo(&lifo);
    
    return 0;
    */

    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite s1;
    if ((s1 = CU_add_suite("stack", init, clean)) == NULL) {
        printf("Error in CU_add_suite stack, %s\n", CU_get_error_msg());
		CU_cleanup_registry();
		exit(1);
    }

    CU_add_test(s1, "push1", push_test1);
    CU_add_test(s1, "push2", push_test2);
    CU_add_test(s1, "pop1", pop_test1);
    CU_add_test(s1, "pop2", pop_test2);


    CU_pSuite s2;
    if ((s2 = CU_add_suite("calculator", init, clean)) == NULL) {
        printf("Error in CU_add_suite calculator, %s\n", CU_get_error_msg());
		CU_cleanup_registry();
		exit(1);
    }

    CU_add_test(s2, "1 + 3 + 5 + 7 + 9", sum_test);
    CU_add_test(s2, "9 - 7 - 5 - 3 - 1", sub_test);
    CU_add_test(s2, "1 * 3 * 5 * 7 * 9", mult_test);
    CU_add_test(s2, "division by zero", div_test1);
    CU_add_test(s2, "division", div_test2);
    CU_add_test(s2, "9 %% 5", mod_test);
    
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());

    return CU_get_number_of_failures();
}
