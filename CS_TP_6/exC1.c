#include <stdio.h>

typedef struct {
	char *code;
	char *type;
	char *name;
	float price;
	unsigned int stock_quantity;
} Product;

int main() {
	Product motherboard = {"code 1", "Motherboard", "MSI H110M PRO-VD", 100, 97};
	Product processor = {"code 2", "Processor", "Intel Core i7 Kaby Lake", 400, 13};
	Product harddisk = {"code 3", "Hard-disk", "Western Digital WD Blue Desktop 1 TB (WD10EZRZ)", 60, 129};
	Product graphic = {"code 4", "Graphic", "Palit GeForce GTX 1060 1506Mhz PCI-E 3.0 6144Mb 8000Mhz 192 bit DVI HDMI HDCP 4.5", 350, 54};
	printf("%s\n", motherboard.code);
	printf("%s", motherboard.type);

	printf("\n");
	return 0;
}
