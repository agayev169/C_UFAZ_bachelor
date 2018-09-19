#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int c;
    int oa = 0;
    int ob = 0;
    int oc = 0;

    while((c = getopt(argc, argv, "a:bc")) != -1) {
        switch(c) {
            case 'a':
                oa = 1;
                break;
            case 'b':
                ob = 1;
                break;
            case 'c':
                oc = 1;
                break;

            case '?':
                // printf("Unknown option: %c\n", optopt);
                // if (optopt == 'a') {
                //     printf("Option -a needs more arguments\n");
                // }

                break;

            default:
                printf("Unknown option!\n");
                break;
        }
    }    

    printf("oa: %d, ob: %d, oc: %d\n", oa, ob, oc);

    return 0;
}