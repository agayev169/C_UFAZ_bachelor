#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int len(char *str);

int main(int argc, char *argv[]) {
    /*
    int fd = open("test.txt", O_CREAT | O_WRONLY, 00600);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    char *str = "Si ton tonton tond mon tonton\n";
    write(fd, str, len(str));
    */
    
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    char buf[20];
    read(fd, buf, 20);
    buf[19] = '\0';
    printf("%s", buf);

    close(fd);
    return 0;
}

int len(char *str) {
    int count = 0;
    while(str[count] != '\0') {
        count++;
    }
    return count;
}