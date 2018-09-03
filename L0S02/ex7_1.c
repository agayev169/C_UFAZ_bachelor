#include <stdio.h>

typedef struct product {
    float price;
    int qty;
} Product;

void save(Product list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("A product #%d:\n", i);
        scanf("%f %d", &(list[i].price), &(list[i].qty));
    }
}

void show(Product list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("A product #%d:\n", i);
        printf("%f %d\n", (list[i].price), (list[i].qty));
    }
}

float getPrice(Product list[], int index) {
    return list[index].price;
}

int main() {
    int n;
    printf("Number of elements: ");
    scanf("%d", &n);
    
    Product list[n];

    save(list, n);
    show(list, n);

    int index;
    scanf("%d", &index);
    printf("Price of product #%d: %f\n", index, getPrice(list, index));

    return 0;
}