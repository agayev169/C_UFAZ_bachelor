#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

int main(int argc, char const *argv[]) {
    BinaryTreeInt *tree = NULL;

    char ans;
    int num;

    int arr[] = {20, 10, 5, 15, 12, 17, 30, 25, 35};

    for (int i = 0; i < 9; i++) {
        add(&tree, arr[i]);
    }

    while (1) {
        printf("(a)dd, (p)rint in ascending order, (P)rint as tree, \n(n)umber of nodes, (f)ind a value, (d)epth, print (l)evels, (b)reak, (D)elete: ");
        scanf(" %c", &ans);
        if (ans == 'a') {
            printf("Enter a number to add into tree: ");
            scanf("%d", &num);
            add(&tree, num);
        } else if (ans == 'p') {
            printTreeAsc(tree);
            printf("\n");
		} else if (ans == 'P') {
            printAsTree(tree);
            printf("\n");
		} else if (ans == 'n') {
            int num = 0;
            treeNodeNumber(tree, &num);
            printf("%d\n", num);
		} else if (ans == 'f') {
            int num;
            printf("Number: ");
            scanf("%d", &num);
            if (search(tree, num) == 0) printf("Found\n");
            else printf("Not found\n");
		} else if (ans == 'd') {
            printf("Depth: %d\n", treeDepth(tree));
            printf("Depth difference: %d\n", tree->depthDiff);
		} else if (ans == 'D') {
            int num;
            printf("A number to delete: ");
            scanf("%d", &num);
            delete(tree, num);
		} else if (ans == 'l') {
            printLevels(tree);
		} else if (ans == 'b')
            break;
    }

    return 0;
}
