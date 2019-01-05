#pragma once

#include "bmp.hpp"
#include "tensor.hpp"
#include <iostream>
#include <vector>

class Conv {
private:
    std::vector<Tensor<int>> conv_;
    std::vector<std::pair<unsigned int, unsigned int>> pos_;
    void findMaxSTD(const BMPImage &, unsigned int h, 
        int minX = 0, int maxX = -1);
public:
    Conv(unsigned int steps, unsigned int a, unsigned int b, unsigned int c);
    Conv(unsigned int steps, const std::vector<unsigned int> &size);
    Conv(const std::vector<Tensor<int>> &, unsigned int steps);
    Conv(const Conv &);
    std::vector<std::pair<unsigned int, unsigned int>> getPos() const;
    void findMaxSTD(const BMPImage &);
    Conv findSimilar(const BMPImage &) const;
};