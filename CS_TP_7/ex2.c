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
	printf("Price		Quantity\n");
	for (int i = 0; i < n; i++)
		printf("%10.2f%10d\n", product[i].price, product[i].quantity);
}

int main() {
	FILE *fp;
	fp = fopen("products.txt", "r");
	
	printing_db(fp);

	return 0;
}
