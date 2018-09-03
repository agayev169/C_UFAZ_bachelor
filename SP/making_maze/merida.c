#include <stdio.h>

int main() {
	FILE *f, *m;
	m = fopen("merida.pgm", "r");
	f = fopen("foo.pgm", "w");
	char format[2];
	int width, height;
	int resolution;
	fscanf(m, "%s", format);
	fscanf(m, "%d %d", &width, &height);
	fscanf(m, "%d", &resolution);
	int colors[width*height];
	fprintf(f, "%s\n%d %d\n%d\n", format, width, height, resolution);
	for (int i = 0; i < width*height; ++i) {
		fscanf(m, "%d", &(colors[i]));
		colors[i] /= 2;
		fprintf(f, "%d \n", colors[i]);
	}
	// fprintf(f, "%s\n%d %d\n255\n", format, width, height);
	// printf("%s\n%d %d\n%d\n", format, width, height, resolution);
	fclose(f);
	fclose(m);

	return 0;
}