#include <stdio.h>
#include "letters.h"

int main(int argc, char const *argv[]) {
	FILE *f;
	f = fopen("f.pgm", "w");
	int const numberOfLetters = 11;
	int const font_width = 4;
	int const font_height = 5;
	int const width = numberOfLetters * font_width + numberOfLetters + 1, height = 7;
	fprintf(f, "P1\n%d %d\n", width, height);

	int A [20] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1};
	int B [20] = {1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0};
	int C [20] = {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1};
	int D [20] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0};
	int E [20] = {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1};
	int F [20] = {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0};
	int G [20] = {0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1};
	int H [20] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1};
	int I [20] = {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1};
	int J [20] = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int K [20] = {1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1};
	int L [20] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1};
	int M [20] = {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1};
	int N [20] = {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
	int O [20] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
	int P [20] = {1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0};
	int Q [20] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
	int R [20] = {1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1};
	int S [20] = {0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0};
	int T [20] = {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0};
	int U [20] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
	int V [20] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0};
	int X [20] = {1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1};
	int Y [20] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0};
	int Z [20] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
	int space [20] = {0};

	for (int i = 0; i < width; ++i)
		fprintf(f, "0 ");
	fprintf(f, "\n");
	for (int i = 0; i < font_height; ++i) {
		fprintf(f, "0 ");

		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", K[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", A[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", M[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", A[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", space[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", B[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", E[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", S[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", I[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", S[i*font_width+j]);
		}
		fprintf(f, "0 ");
		for (int j = 0; j < font_width; ++j) {
			fprintf(f, "%d ", H[i*font_width+j]);
		}
		fprintf(f, "0 ");		
		fprintf(f, "\n");
	}
	for (int i = 0; i < width; ++i)
		fprintf(f, "0 ");

	return 0;
}