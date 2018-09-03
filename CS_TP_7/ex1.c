#include <stdio.h>

typedef struct {
	float price;
	unsigned int quantity;
} Product;

void saving_db(FILE *fp) {
	printf("Number of products: ");
	unsigned int n;
	scanf("%d", &n);
	Product product[n];
	for(int i = 0; i < n; i++) {
		printf("Price of product #%d: ", i+1);
		scanf("%f", &product[i].price);
		printf("Quantity of product #%d: ", i+1);
		scanf("%d", &product[i].quantity);
	}
	fprintf(fp, "%d\n", n);
	for(int i = 0; i < n; i++)
		fprintf(fp, "%.2f    %d\n", product[i].price, product[i].quantity);
}

int main() {
	FILE *fp;
	fp = fopen("products.txt", "w");
	
	saving_db(fp);

	return 0;
}
