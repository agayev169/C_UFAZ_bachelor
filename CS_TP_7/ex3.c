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
	printf("You want to know the price of element #");
	int element;
	scanf("%d", &element);
	while (element < 0 && element > n) scanf("%d", &element);
	printf("Price of element #%d is %.2f\n", element, product[element-1].price);
}

int main() {
	FILE *fp;
	fp = fopen("products.txt", "r");
	
	printing_db(fp);

	return 0;
}
