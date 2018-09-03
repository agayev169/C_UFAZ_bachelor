#ifndef __BMP_H__
#define __BMP_H__

typedef struct {
    int width;
    int height;
    // Pixel **pixels;
    unsigned char *vals;
    char *header;
    int sizeOfHeader;
    int bytesPerPixel;
} BMPImage;

BMPImage read(char *fileName);
// BMPImage crop(BMPImage InitImg, int stripSize);
void cropAndSave(BMPImage img, int stripSize, char *fileName);
void readAndCropAndSave(char *fileName, int stripSize);
// void save(BMPImage initImg);
char* itoa(int val);
int digitsInNum(int num);

#endif