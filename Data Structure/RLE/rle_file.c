#include <stdio.h>
#include <stdlib.h>

void compress(char *filename_in, char *filename_out);
void compress2(char *filename_in, char *filename_out);
void decompress(char *filename_in, char *filename_out);
void decompress2(char *filename_in, char *filename_out);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("You need to pass input file and output files\n");
		exit(1);
	}
    compress2(argv[1], argv[2]);

    return 0;
}

// Compression

void compress(char *filename_in, char *filename_out) {
    // Compresses indicating only the number of same chars even if the number == 1
    // Not Recomended

    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");
    char c;
    fread(&c, 1, 1, f_in);
    char prev;
    int count = 1;

    while(!feof(f_in)) {
        prev = c;
        fread(&c, 1, 1, f_in);
        if (c == prev) {
            count++;
        } else {
            fwrite(&count, 4, 1, f_out);
            fwrite(&prev, 1, 1, f_out);
            count = 1;
        }
    }
    count--;
    fwrite(&count, 4, 1, f_out);
    fwrite(&prev, 1, 1, f_out);

    fclose(f_in);
    fclose(f_out);
}

void compress2(char *filename_in, char *filename_out) {
    // Compresses indicating both the number of same chars and different chars
    // Recomended
    
    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");

    fseek(f_in, 0, SEEK_END);
    int end = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);

    char c;
    fread(&c, 1, 1, f_in);
    char prev;
    int count_same = 1;
    int count_dif = 0;


    while(!feof(f_in)) {
        if (ftell(f_in) == end) break;
        prev = c;
        fread(&c, 1, 1, f_in);
        if (c == prev && count_dif == 0) {
            count_same++;
        } else if (c == prev && count_dif > 0) {
            fseek(f_in, -count_dif - 2, SEEK_CUR);
            char *tmp = (char*) calloc(count_dif, sizeof(char));
            fread(tmp, 1, count_dif, f_in);
            count_dif *= -1;
            fwrite(&count_dif, 4, 1, f_out);
            fwrite(tmp, 1, -count_dif, f_out);
            count_dif = 0;
            fread(&c, 1, 1, f_in);
            count_same = 1;
        } else if (count_same > 1) {
            fwrite(&count_same, 4, 1, f_out);
            fwrite(&prev, 1, 1, f_out);
            count_same = 1;
        } else {
            count_dif++;
        }
    }
    if (count_same > 1) {
        fwrite(&count_same, 4, 1, f_out);
        fwrite(&prev, 1, 1, f_out);
    } else {
        fseek(f_in, -count_dif - 1, SEEK_CUR);
        char *tmp = (char*) calloc(count_dif + 1, sizeof(char));
        fread(tmp, 1, count_dif + 1, f_in);
        int count_dif_tmp = count_dif;
        count_dif = -(count_dif + 1);
        fwrite(&count_dif, 4, 1, f_out);
        fwrite(tmp, 1, count_dif_tmp + 1, f_out);
    }

    fclose(f_in);
    fclose(f_out);
}

// Decompression

void decompress(char *filename_in, char *filename_out) {
    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");

    fseek(f_in, 0, SEEK_END);
    long end = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);
    while(!feof(f_in)) {
        int size;
        fread(&size, 4, 1, f_in);
        char c;
        fread(&c, 1, 1, f_in);
        if (ftell(f_in) == end) break;
        for (int i = 0; i < size; i++) {
            fprintf(f_out, "%c", c);
        }
    }

    fclose(f_in);
    fclose(f_out);
}

void decompress2(char *filename_in, char *filename_out) {
    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");

    while(!feof(f_in)) {
        int size;
        fread(&size, 4, 1, f_in);
        if (size > 0) {
            char c;
            fread(&c, 1, 1, f_in);
            for (int i = 0; i < size; i++) {
                fprintf(f_out, "%c", c);
            }
        } else if (size < 0) {
            char *str;
            str = (char*) calloc(-size, sizeof(char));
            fread(str, 1, -size, f_in);
            fprintf(f_out, "%s", str);
        }
    }

    fclose(f_in);
    fclose(f_out);
}
