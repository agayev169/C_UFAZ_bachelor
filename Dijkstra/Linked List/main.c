#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main(int argc, char const *argv[]) {
    LinkedListInt *list = NULL;

    char ans;
    int num;

    while (1) {
        printf("(a)dd, (s)orted addition, (d)elete, (D)estroy, (p)rint, (b)reak: ");
        scanf(" %c", &ans);
        if (ans == 'a') {
            printf("Enter a number to add into list: \n");
            scanf("%d", &num);
            add(&list, num);
        } else if (ans =='d') {
            printf("Enter a number to remove from list: \n");
            scanf("%d", &num);
            del(&list, num);
        } else if (ans == 'p') {
            printDescR(list);
            printf("\n");
        }
        else if (ans == 'b')
            break;
        else if (ans == 's') {
            printf("Enter a number to add into sorted list: \n");
            scanf("%d", &num);
            sortedAdd(&list, num);
        } else if (ans == 'D')
            destroy(&list);
        else
            printf("Unknown symbol\n");
    }

    destroy(&list);

    return 0;
}
