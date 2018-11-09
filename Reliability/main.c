#include <stdio.h>

double mult_of_array(double *arr, int size);

int main(int argc, char *argv[]) {
    int model = -1;
    double reliability = 0;
    printf("Reliability: ");
    scanf("%lf", &reliability);
    double system_reliability = 0;
    double safe_failure = 0;
    double dangerous_failure = 0;
    for (int model = 1; model <= 3; model++) {
        printf("\n");
        if (model == 1) {
            printf("2oo2\n");
            double probs[4][2];
            for (int i = 0; i < 4; i++) {
                int tmp = i;
                for (int j = 0; j < 2; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                }
            }

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 2; j++) {
                    printf("%.5f  ", probs[i][j]);
                }
                printf("\n");
            }
            system_reliability = mult_of_array(probs[0], 2);
            safe_failure = mult_of_array(probs[1], 2) + mult_of_array(probs[2], 2);
            dangerous_failure = mult_of_array(probs[3], 2);
        } else if (model == 2) {
            printf("2oo3\n");
            double probs[8][3];
            for (int i = 0; i < 8; i++) {
                int tmp = i;
                for (int j = 0; j < 3; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                }
            }

            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 3; j++) {
                    printf("%.5f  ", probs[i][j]);
                }
                printf("\n");
            }
            system_reliability = mult_of_array(probs[0], 3) + mult_of_array(probs[1], 3) + 
                mult_of_array(probs[2], 3) + mult_of_array(probs[4], 3);
            safe_failure = 0;
            dangerous_failure = mult_of_array(probs[3], 3) + mult_of_array(probs[5], 3) + 
                mult_of_array(probs[6], 3) + mult_of_array(probs[7], 3);
        } else if (model == 3) {
            printf("2oo2x2\n");
            double probs[16][4];
            for (int i = 0; i < 16; i++) {
                int tmp = i;
                for (int j = 0; j < 4; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                }
            }

            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 4; j++) {
                    printf("%.5f  ", probs[i][j]);
                }
                printf("\n");
            }
            system_reliability = mult_of_array(probs[0], 4) + mult_of_array(probs[1], 4) + 
                mult_of_array(probs[2], 4) + mult_of_array(probs[4], 4) + 
                mult_of_array(probs[8], 4);
            safe_failure = mult_of_array(probs[5], 3) + mult_of_array(probs[6], 3) + 
                mult_of_array(probs[9], 4) + mult_of_array(probs[10], 4);
            dangerous_failure = mult_of_array(probs[3], 4) + mult_of_array(probs[7], 3) + 
                mult_of_array(probs[11], 3) + mult_of_array(probs[12], 3) + 
                mult_of_array(probs[13], 3) + mult_of_array(probs[14], 3) + 
                mult_of_array(probs[15], 3);
        }
        printf("Reliability of a system: %.10lf\n", system_reliability);
        printf("Safe failure rate of a system: %.10lf\n", safe_failure);
        printf("Dangerous failure rate of a system: %.10lf\n", dangerous_failure);
    }

    return 0;
}

double mult_of_array(double *arr, int size) {
    double mult = 1;
    for (int i = 0; i < size; i++) {
        mult *= arr[i];
    }
    return mult;
}
