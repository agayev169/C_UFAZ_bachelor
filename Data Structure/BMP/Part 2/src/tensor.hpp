#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

template <class T>
class Tensor { // Class of Tensor - 3D list to easily operate with pixels
private:
    std::vector<unsigned int> size_;
public:
    std::vector<std::vector<std::vector<T>>> data_;
    Tensor(const std::vector<std::vector<std::vector<T>>> &data);
    Tensor(const std::vector<unsigned int> &size);
    Tensor(unsigned int, unsigned int, unsigned int);
    Tensor(const Tensor &);
    Tensor operator+(const Tensor &) const;
    Tensor operator+=(const Tensor &);
    Tensor operator-(const Tensor &) const;
    Tensor operator-=(const Tensor &);
    Tensor operator*(int) const;
    Tensor operator*=(T);
    double dist(const Tensor &t) const;
    double mean() const;
    double std() const;
    std::vector<unsigned int> getSize() const;
    void normalize();
    void urandom(int = 255);

    void print(std::ostream &) const;
};

template <class T>
std::ostream &operator<<(std::ostream &, const Tensor<T> &);