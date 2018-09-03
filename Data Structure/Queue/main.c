#include <stdio.h>
#include "queue.h"

int main(int argc, char const *argv[]) {
    int n;
    Fifo myFifo;

    createFifo(&myFifo, 5);

    do {
        printf("\n");
        printf("Enter any number to enqueue, -2 to dequeue, -3 to print,\n-4 to print whole queue, -5 to destroy, -1 to finish: ");
        scanf("%d", &n);
        printf("\n");
        if (n == -1)
            break;
        else if (n == -2) {
            int ans;
            if ((ans = dequeue(&myFifo)) != -1)
                printf("Dequeued value: %d\n", ans);
        } else if (n == -3)
            printQueue(myFifo);
        else if (n == -4)
            printAll(myFifo);
        else if (n == -5) {
            destroy(&myFifo);
            printf("Queue was destroyed\n");
        } else if (enqueue(&myFifo, n) == 0)
                printf("%d was enqueued\n", n);
    } while (1);

    // printf("Enqueue numbers (-1 to finish)\n");
    // scanf("%d", &n);
    // while (n != -1) {
    //     if (enqueue(&myFifo, n)) {
    //         fprintf(stderr, "Error enqueue\n");
    //         return 1;
    //     }
    //     printQueue(&myFifo);
    //     printAll(&myFifo);
    //     scanf("%d", &n);
    // }
    //
    //
    // n = 1;
    // printf("Dequeue?(Any button/-1): ");
    // scanf("%d", &n);
    // while (n != -1) {
    //     int ans;
    //     if ((ans = dequeue(&myFifo)) == -1) {
    //         fprintf(stderr, "Error dequeue\n");
    //         return 1;
    //     }
    //     printf("Dequeued value: %d\n", ans);
    //     printQueue(&myFifo);
    //     scanf("%d", &n);
    // }

    destroy(&myFifo);

    return 0;
}
