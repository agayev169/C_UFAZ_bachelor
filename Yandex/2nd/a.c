#include <stdio.h>

int isFound(int user, int target[]) {
    for (int i = 0; i < 10; i++) {
        if (user == target[i]) return 1;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    // printf("Targets: ");
    int target[10];
    for (int i = 0; i < 10; i++) {
        scanf("%d", &target[i]);
    }
    // printf("Number of users\n");
    int n;
    scanf("%d", &n);
    int user[n][6];
    for (int i = 0; i < n; i++) {
        // printf("Numbers of user %d: ", i);
        for (int j = 0; j < 6; j++) {
            scanf("%d", &user[i][j]);
        }
    }
    // printf("Got\n");
    for (int i = 0; i < n; i++) {
        int counter = 0;
        for (int j = 0; j < 6; j++) {
            counter += isFound(user[i][j], target);
        }
        printf(counter >= 3 ? "Lucky\n" : "Unlucky\n");
    }

    return 0;
}
