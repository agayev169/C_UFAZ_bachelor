#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

void readAndCropAndSave(char *fileName, int stripSize) {
    BMPImage img = read(fileName);

    int digits = digitsInNum(stripSize);

    int size = 0;
    for (int i = 0; fileName[i] != '\0'; i++) size++;
    // printf("Size of fileName: %d\n", size);

    char *newName = (char*) calloc(size + digits + 6, sizeof(char));

    if (strncmp(&(fileName[size - 4]), ".bmp", 4) == 0) size -= 4;
    for (int i = 0; i < size; i++) {
        newName[i] = fileName[i];
    }
    strcat(newName, "_S");
    strcat(newName, itoa(stripSize));
    strcat(newName, ".bmp");
    
    cropAndSave(img, stripSize, newName);
}

BMPImage read(char *fileName) {
    if (!fileName) { // Check if any argument is passed 
        fprintf(stderr, "Error! Cannot open the file\n");
        exit(0);
    }

    FILE *file = fopen(fileName, "rb");

    if (!file) { //Check if file is opened
        fprintf(stderr, "Error! Cannot open the file\n");
        exit(0);
    }

    BMPImage img;
    // BMP Header

    // First 2 bytes (BM)
    char ch[2];
    fread(ch, 1, 2, file);
    if (!(ch[0] == 'B' && ch[1] == 'M')) { // Check if a file is of BMP format
        fprintf(stderr, "Error! %s is not a BMP file!\n", fileName);
        exit(0);
    }

    // Size of file
    int size;
    fread(&size, 1, 4, file);
    // printf("size: %d\n", size);

    // 4 bytes reserved for application
    fseek(file, 4, SEEK_CUR);

    // pixels' start
    int start;
    fread(&start, 1, 4, file);
    img.sizeOfHeader = start;
    // printf("%d", start);

    // DIB Header

    // Size of DIB header
	fseek(file, 4, SEEK_CUR);    

    fseek(file, 0, SEEK_SET);
    img.header = (char*) calloc(img.sizeOfHeader, sizeof(char));
    fread(img.header, start, 1, file);
    fseek(file, 18, SEEK_SET);

    // Width of image
    int width;
    fread(&width, 1, 4, file);
    // printf("%d", width);

    // Height of image
    int height;
    fread(&height, 1, 4, file);
    // printf("%d", height);

    // Number of color panels
    fseek(file, 2, SEEK_CUR);

    // Nubmer of bits for pixel
    short bitsPerPixel;
    fread(&bitsPerPixel, 1, 2, file);
    // printf("Bits per pixel: %d\n", bitsPerPixel);

    // Finally pixels!
    fseek(file, start, SEEK_SET);

    // Creating an image
    
    img.width = width;
    img.height = height;
    img.bytesPerPixel = bitsPerPixel / 8;
    img.vals = (unsigned char*) calloc(width * height * img.bytesPerPixel, sizeof(unsigned char));

    // Reading the whole image
    fread(img.vals, 1, width * height * img.bytesPerPixel, file);
    // printf("size: %d, size of header: %d, width: %d, height: %d\n", size, img.sizeOfHeader, img.width, img.height);
    fclose(file);
    
    return img;
}

// BMPImage crop(BMPImage img, int stripSize) {
void cropAndSave(BMPImage img, int stripSize, char *fileName) {

    int padding = (4 - (stripSize * img.bytesPerPixel) % 4) % 4;

    // New width
    int width = stripSize;

    int start = img.width / 2 - stripSize / 2;
    // printf("initImg.width: %d, stripSize: %d, start: %d\n", img.width, stripSize, start);

    FILE *file = fopen(fileName, "wr");

    // Writing a header of original file
    fwrite(img.header, img.sizeOfHeader, 1, file);

    // Changing size of file
    fseek(file, 2, SEEK_SET);
    int size = img.sizeOfHeader + img.bytesPerPixel * width * img.height;
    fwrite(&size, 1, 4, file);
    // printf("size: %d, size of header: %d, width: %d, height: %d\n", size, img.sizeOfHeader, img.width, img.height);

    // Changing width of image
    fseek(file, 18, SEEK_SET);
    fwrite(&width, 1, 4, file);
    fseek(file, img.sizeOfHeader, SEEK_SET);

    int zero = 0;
    for (int y = 0; y < img.height; y++) {
        fwrite(&(img.vals[(y * img.width + start) * img.bytesPerPixel]), 1, width * img.bytesPerPixel, file);
        if (padding)
            fwrite(&zero, 1, padding, file);
    }
}

char* itoa(int val) {
	static char buf[10] = {0};
	int i = 9;
	for(; val && i ; i--, val /= 10)
		buf[i] = "0123456789"[val % 10];
	
	return &buf[i+1];
}

int digitsInNum(int num) {
    int digits = 0;
    for (; num > 0; num /= 10, digits++);
    return digits;
}
