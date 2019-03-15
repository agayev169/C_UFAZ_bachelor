#pragma once

#include "bmp.hpp"
#include "tensor.hpp"
#include <iostream>
#include <vector>

class Marker { // A marker class to 
private:
    std::vector<Tensor<int>> data_;
    std::vector<std::pair<unsigned int, unsigned int>> pos_;
    void findMaxSTD(const BMPImage &img, unsigned int h, 
        int minX = 0, int maxX = -1);
public:
    Marker(unsigned int steps, unsigned int a, unsigned int b, unsigned int c);
    Marker(unsigned int steps, const std::vector<unsigned int> &size);
    Marker(const std::vector<Tensor<int>> &, unsigned int steps);
    Marker(const Marker &);
    std::vector<std::pair<unsigned int, unsigned int>> getPos() const;
    void findMaxSTD(const BMPImage &);
    Marker findSimilar(const BMPImage &) const;
};