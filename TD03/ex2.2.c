#include <stdio.h>

struct vector {
	int nb_dims;
	float a[4];
};

struct vector V_new(int nb_dims);
void V_allZero2(struct vector *v);
void V_print2(struct vector v);

int main() {
	 struct vector v;
	 v=V_new(3);
	 V_allZero2(&v);
	 V_print2(v);

	return 0;
}
struct vector V_new(int nb_dims) {
	struct vector x;
	x.nb_dims=nb_dims;
	return x;
}

void V_allZero2(struct vector *v) {
	int i;
	for(i=0;i<(*v).nb_dims;i++) {
		(*v).a[i]=0.0f;
	}
}


void V_print2(struct vector v) {
	int i;
	for(i=0;i<v.nb_dims;i++) {
		printf("%f\n",v.a[i]);	
	}
}