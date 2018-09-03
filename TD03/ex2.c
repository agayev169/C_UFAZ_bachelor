#include <stdio.h>

void V_allZero(float vector[], int nb_dims);
void V_print(float vector[], int nb_dims);
void V_belongsTo(float x, float vector[], int nb_dims); 

int main () {
	
	
	return 0;
}


void V_allZero(float vector[], int nb_dims) {
	for (int i = 0; i < nb_dims; i++) vector[i] = 0.0f;
}
void V_print(float vector[], int nb_dims) {	
	for (int i = 0; i < nb_dims; i++) printf("%f", vector[i]);
}
void V_belongsTo(float x, float vector[], int nb_dims) {
	for (int i = 0; i < nb_dims; i++) {
		if (vector[i] == x) return 1;
	}
	return 0;
}
