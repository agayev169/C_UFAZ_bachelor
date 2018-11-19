#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        FILE *csv_file;
        if (model == 1) {
            char filename[50] = "2oo2_rel-";
            char rel_str[10];
            snprintf(rel_str, 10, "%lf", reliability);
            strcat(filename, rel_str);
            strcat(filename, ".csv");
            csv_file = fopen(filename, "w");
            printf("2oo2\n");
            double probs[4][3];
            for (int i = 0; i < 4; i++) {
                int tmp = i;
                double mult = 1.0;
                for (int j = 0; j < 2; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                    mult *= probs[i][j];
                }
                probs[i][2] = mult;
            }

            fprintf(csv_file, "A,B,Result\n");
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    printf("%.10f  ", probs[i][j]);
                    fprintf(csv_file, "%.10f,", probs[i][j]);
                }
                printf("\n");
                fprintf(csv_file, "\n");
            }
            system_reliability = probs[0][2];
            safe_failure = probs[1][2] + probs[2][2];
            dangerous_failure = probs[3][2];
            fprintf(csv_file, "Reliability,Safe Failure,Dangerous Failure\n");
            fprintf(csv_file, "%.10lf,%.10lf,%.10lf", system_reliability, safe_failure,
            dangerous_failure);
            fclose(csv_file);
        } else if (model == 2) {
            char filename[50] = "2oo3_rel-";
            char rel_str[10];
            snprintf(rel_str, 10, "%lf", reliability);
            strcat(filename, rel_str);
            strcat(filename, ".csv");
            csv_file = fopen(filename, "w");
            printf("2oo3\n");
            double probs[8][4];
            for (int i = 0; i < 8; i++) {
                int tmp = i;
                double mult = 1.0;
                for (int j = 0; j < 3; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                    mult *= probs[i][j];
                }
                probs[i][3] = mult;
            }

            fprintf(csv_file, "A,B,C,Result\n");
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 4; j++) {
                    printf("%.10f  ", probs[i][j]);
                    fprintf(csv_file, "%.10f,", probs[i][j]);
                }
                printf("\n");
                fprintf(csv_file, "\n");
            }
            system_reliability = probs[0][3] + probs[1][3] + 
                probs[2][3] + probs[4][3];
            safe_failure = 0;
            dangerous_failure = probs[3][3] + probs[5][3] + 
                probs[6][3] + probs[7][3];
            fprintf(csv_file, "Reliability,Safe Failure,Dangerous Failure\n");
            fprintf(csv_file, "%.10lf,%.10lf,%.10lf", system_reliability, safe_failure,
            dangerous_failure);
            fclose(csv_file);
        } else if (model == 3) {
            char filename[50] = "2oo2x2_rel-";
            char rel_str[10];
            snprintf(rel_str, 10, "%lf", reliability);
            strcat(filename, rel_str);
            strcat(filename, ".csv");
            csv_file = fopen(filename, "w");
            printf("2oo2x2\n");
            double probs[16][5];
            for (int i = 0; i < 16; i++) {
                int tmp = i;
                double mult = 1.0;
                for (int j = 0; j < 4; j++) {
                    probs[i][j] = (tmp % 2 == 0) ? reliability: 1 - reliability;
                    tmp /= 2;
                    mult *= probs[i][j];
                }
                probs[i][4] = mult;
            }

            fprintf(csv_file, "A,B,C,D,Result\n");
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 5; j++) {
                    fprintf(csv_file, "%.10f,", probs[i][j]);
                    printf("%.10f  ", probs[i][j]);
                }
                printf("\n");
                fprintf(csv_file, "\n");
            }
            system_reliability = probs[0][4] + probs[1][4] + 
                probs[2][4] + probs[4][4] + probs[8][4];
            safe_failure = probs[5][4] + probs[6][4] + 
                probs[9][4] + probs[10][4];
            dangerous_failure = probs[3][4] + probs[7][4] + 
                probs[11][4] + probs[12][4] + probs[13][4] +
                probs[14][4] + probs[15][4];
            fprintf(csv_file, "Reliability,Safe Failure,Dangerous Failure\n");
            fprintf(csv_file, "%.10lf,%.10lf,%.10lf", system_reliability, safe_failure,
            dangerous_failure);
            fclose(csv_file);
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
