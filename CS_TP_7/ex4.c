#include <stdio.h>

typedef struct {
	float price;
	unsigned int quantity;
} Product;

void printing_db(FILE *fp) {
	int n;
	fscanf(fp, "%d", &n);
	Product product[n];
	for (int i = 0; i < n; i++)
		fscanf(fp, "%f%d", &product[i].price, &product[i].quantity);
	
	FILE *c;
	if ((c = fopen("command.txt", "r"))==NULL) printf("Error!");
	else {
		float result = 0;
		unsigned int c_code, c_quantity;
		while (!feof(c)) {
			fscanf(c, "%d%d", &c_code, &c_quantity);
			if (c_quantity <= product[c_code-1].quantity) {
				result += c_quantity * product[c_code-1].price;
				product[c_code-1].quantity -= c_quantity;
			} else {
				printf("There is only %d products of code %d\n", product[c_code-1].quantity, c_code);
				result += product[c_code-1].quantity * product[c_code-1].price;
				product[c_code-1].quantity = 0;
			}
		}
	printf("%f", result);

	fp = fopen("products.txt", "w");
	fprintf(fp, "%d\n", n);
	for (int i = 0; i < n; i++)
		fprintf(fp, "%.2f	%d\n", product[i].price, product[i].quantity);
	}
}

int main() {
	FILE *fp;
	fp = fopen("products.txt", "r");
	
	printing_db(fp);

	return 0;
}
