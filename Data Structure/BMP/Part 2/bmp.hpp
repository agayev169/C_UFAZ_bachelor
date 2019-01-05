#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

class BMPImage {
private:
    unsigned int width_;
    unsigned int height_;
    unsigned int sizeOfHeader_;
    unsigned int bytesPerPixel_ = 0;
    char *header_ = NULL;
    std::string name;
    BMPImage();
public:
    unsigned char *pixels_ = NULL;
    BMPImage(const std::string &fileName);
    BMPImage(const std::string &fileName, int stripSize);
    BMPImage(const BMPImage &original, unsigned int width, unsigned int height);
    BMPImage(const BMPImage &original);
    ~BMPImage();
    void save(const std::string &fileName) const;
    void cropAndSave(const std::string &fileName, int stripSize) const;
    BMPImage cropStrip(unsigned int stripSize) const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    BMPImage scaleBasedOnPSF(const std::vector<float> &psf) const; 
    unsigned int getBytesPerPixel() const;
};

float max(const std::vector<float> &v);
std::string itoa(int val);