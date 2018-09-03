#include <stdio.h>

typedef struct {
	char code;
	char *type;
	char *name;
	float price;
	unsigned int stock_quantity;
} Product;

Product getProduct();
void showProduct(Product product);

int main() {
	Product motherboard = {'0', "Motherboard", "MSI H110M PRO-VD",0 ,0 };

	printf("Name: %s", motherboard.name);
	printf("\n");
	printf("Type: %s", motherboard.type);
	printf("\n\n");
	printf("Code: ");
	
	motherboard = getProduct();
	

	printf("\n");
	return 0;
}

Product getProduct() {
	Product product = {'0', "Motherboard", "MSI H110M PRO-VD",0 ,0 };
	scanf("%s", &product.code);
	printf("Price: ");
	scanf("%f", &product.price);
	printf("Stock Quantity: ");
	scanf("%d", &product.stock_quantity);
	printf("\n");
	
	showProduct(product);
	
	return product;
}

void showProduct(Product product) {
	printf("Name: %s", product.name);
	printf("\n");
	printf("Type: %s", product.type);
	printf("\n");
	printf("Code: ");
	printf("Code %c", product.code);
	printf("\n");
	printf("Price: %.2f", product.price);
	printf("\n");
	printf("Stock Quantity: %d\n", product.stock_quantity);
	printf("The price of your command: %.2f", (float)product.price * product.stock_quantity);
}
