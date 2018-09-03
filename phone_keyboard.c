#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Клавиши клавиатуры в виде отдельных массивов
char two[] = {"abc"};
char three[] = {"def"};
char four[] = {"ghi"};
char five[] = {"jkl"};
char six[] = {"mno"};
char seven[] = {"pqrs"};
char eight[] = {"tuv"};
char nine[] = {"wxyz"};
char zero[] = {" "};

// Вся клавиатура вместе, чтобы можно было расчитать нажатие каждой отдельной кнопки
char *keyboard[9] = {two, three, four, five, six, seven, eight, nine, zero};

// Объявление функций (Описание функций приведено после main)
void translate(char* input, char* result);
int isSameArray(char a, char b);
char fromArray(char a, int *clicks);

int main(int argc, char const *argv[]) {
    int inputs; // Количество вводимых данных
    scanf("%d", &inputs);
    int inputSizeMax = 15; // Максимальное количество букв в каждой вводимой данной (Можно менять)
    char **result = (char**)calloc(inputs, inputSizeMax * 5); // Создания массива строк
    for (int i = 0; i < inputs; i++) {
        char *input = (char*)calloc(inputSizeMax, 1); // Создание строки для вводимой данной
        scanf(" %[^\n]s", input);
        int inputSize = strlen(input);
        result[i] = (char*)calloc(inputSize * 5, 1); // Создание строки для каждой отдельно взятой вводимой данной 
        translate(input, result[i]);
    }
    for (int i = 0; i < inputs; i++) 
        printf("Case #%d: %s\n", i + 1, result[i]);


    return 0;
}

void translate(char* input, char* result) {
    // Функция для перевода вводной данной в набор цифр
    // Принимает вводимую строку и выходную строку для хранения результата перевода
    int size = strlen(input); // Количество букв в вводимой данной
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (i != 0 && !isSameArray(input[i], input[i - 1])) { 
            // Если i-ая буква не самая первая и находится за одной и той же цифрой что и предыдущая, то... 
            result[count] = ' ';
            count++;
        }
        int clicks = 0;
        char digit = fromArray(input[i], &clicks); // Вычисляем под какой цифрой находится i-ая буква и сколько раз надо нажимать на эту цифру
        // Дописываем в результат столько раз цифру под которой находится буква, сколько надо её нажимать... Ну ты понял :D
        for (int j = 0; j < clicks; j++) {
            result[count] = digit;
            count++;
        }
    }
}

char fromArray(char a, int *clicks) {
    // Функция для нахождения цифры, под которой находится данная буква
    // Принимает букву и адрес целочисленной переменной, в которую будет помещена информация о том, сколько раз надо нажимать цифру
    // для ввода буквы (О том почему передается адрес читай тут https://www.tutorialspoint.com/cprogramming/c_function_call_by_reference.htm)
    for (int i = 0; i < 9; i++) {
        // Ищем под каждой цифрой данную букву
        int count = 0;
        while (keyboard[i][count] != '\0') {
            if (keyboard[i][count] == a) {
                // Если цифра найдена, то сохранем в clicks количество нажатий и возвращаем цифру
                *clicks = count + 1;
                return (i + 2) % 10 + '0'; // Немножко по-идиотски это написал, если интересно что это означает, то читай тут https://stackoverflow.com/questions/2279379/how-to-convert-integer-to-char-in-c
            }
            count++;
        }
    }
    // Это значение по умолчанию, если вдруг ты ввёл что-то кроме латинских букв
    return '-';
}

int isSameArray(char a, char b) {
    // Фунция для определения того, находятся ли две буквы под одной и той же цифрой
    // Если да, то возвращает 0, иначе - 1 
    int clicks = 0;
    char arrayA = fromArray(a, &clicks);
    char arrayB = fromArray(b, &clicks);
    return arrayA == arrayB ? 0 : 1;
}