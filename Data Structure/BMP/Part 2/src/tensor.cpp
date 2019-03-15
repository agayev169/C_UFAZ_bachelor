#include "tensor.hpp"

// Constructors
template <class T> 
Tensor<T>::Tensor(const std::vector<std::vector<std::vector<T>>> &data): data_(data), 
    size_{(unsigned int) data.size(), (unsigned int) data[0].size(), 
        (unsigned int) data[0][0].size()} {}

template <class T> 
Tensor<T>::Tensor(const std::vector<unsigned int> &size): size_(size), 
    data_(size[0], std::vector<std::vector<T>>(size[1], std::vector<T>(size[2]))) {}

template <class T> 
Tensor<T>::Tensor(unsigned int a, unsigned int b, unsigned int c): size_{a, b,  c},
    data_(a, std::vector<std::vector<T>>(b, std::vector<T>(c))) {}

// Copy constructor
template <class T> 
Tensor<T>::Tensor(const Tensor &t): size_(t.size_), data_(t.data_) {}

template <class T> 
Tensor<T> Tensor<T>::operator+(const Tensor<T> &t) const {
    Tensor result(size_);
    if (size_ == t.size_) {
        for (auto i = 0u; i < size_[0]; ++i) {
            for (auto j = 0u; j < size_[1]; ++j) {
                for (auto k = 0u; k < size_[2]; ++k) {
                    result.data_[i][j][k] = data_[i][j][k] + t.data_[i][j][k];
                }
            }
        }
    } else {
        std::cerr << "Error in +. Sizes of matrices are different" << std::endl;
    }
    return result;
}

template <class T> 
Tensor<T> Tensor<T>::operator+=(const Tensor<T> &t) {
    if (size_ == t.size_) {
        for (auto i = 0u; i < size_[0]; ++i) {
            for (auto j = 0u; j < size_[1]; ++j) {
                for (auto k = 0u; k < size_[2]; ++k) {
                    data_[i][j][k] += t.data_[i][j][k];
                }
            }
        }
    } else {
        std::cerr << "Error in +=. Sizes of matrices are different" << std::endl;
    }
    return *this;
}

template <class T> 
Tensor<T> Tensor<T>::operator-(const Tensor<T> &t) const {
    Tensor<T> result(size_);
    if (size_ == t.size_) {
        for (auto i = 0u; i < size_[0]; ++i) {
            for (auto j = 0u; j < size_[1]; ++j) {
                for (auto k = 0u; k < size_[2]; ++k) {
                    result.data_[i][j][k] = data_[i][j][k] - t.data_[i][j][k];
                }
            }
        }
    } else {
        std::cerr << "Error in -. Sizes of matrices are different" << std::endl;
    }
    return result;
}

template <class T> 
Tensor<T> Tensor<T>::operator-=(const Tensor<T> &t) {
    if (size_ == t.size_) {
        for (auto i = 0u; i < size_[0]; ++i) {
            for (auto j = 0u; j < size_[1]; ++j) {
                for (auto k = 0u; k < size_[2]; ++k) {
                    data_[i][j][k] -= t.data_[i][j][k];
                }
            }
        }
    } else {
        std::cerr << "Error in -=. Sizes of matrices are different" << std::endl;
    }
    return *this;
}

template <class T> 
Tensor<T> Tensor<T>::operator*(int x) const {
    Tensor result(size_);
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            for (auto k = 0u; k < size_[2]; ++k) {
                result.data_[i][j][k] = data_[i][j][k] * x;
            }
        }
    }
    return result;
}

template <class T> 
Tensor<T> Tensor<T>::operator*=(T x) {
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            for (auto k = 0u; k < size_[2]; ++k) {
                data_[i][j][k] *= x;
            }
        }
    }
    return *this;
}

// A distance between 2 n-dimensional vectors
template <class T> 
double Tensor<T>::dist(const Tensor<T> &t) const {
    double result = 0.0;
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            for (auto k = 0u; k < size_[2]; ++k) {
                result += (data_[i][j][k] - t.data_[i][j][k]) * (data_[i][j][k] - t.data_[i][j][k]);
            }
        }
    }
    return sqrt(result);
}

// Function to calculate mean value of the Tensor
template <class T> 
double Tensor<T>::mean() const {
    double result = 0.0;
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            double val = 0; // Grayscale value of a pixel
            for (auto k = 0u; k < size_[2] && k < 3; ++k) { // We don't care about alpha value
                val += data_[i][j][k];
            }
            result += val / size_[2];
        }
    }
    return result / size_[0] / size_[1];
}

// Function to calculate STD of the Tensor
template <class T> 
double Tensor<T>::std() const {
    double mean_ = mean();
    double result = 0.0;
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            double val = 0; // Grayscale value of a pixel
            for (auto k = 0u; k < size_[2] && k < 3; ++k) { // We don't care about alpha value
                val += data_[i][j][k];
            }
            result += (val / size_[2] - mean_) * (val / size_[2] - mean_);
        }
    }
    result = result / (size_[0] * size_[1] - 1);
    result = sqrt(result);
    return result;
}

template <class T> 
std::vector<unsigned int> Tensor<T>::getSize() const {
    return size_;
}

// Function to normalize values of the Tensor
template <class T> 
void Tensor<T>::normalize() {
    double mean_ = mean();
    if (mean_ == 0) return;
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            for (auto k = 0u; k < size_[2]; ++k) {
                data_[i][j][k] /= mean_;
            }
        }
    }
}

// Function to randomize the values of a Tensor
template <class T> 
void Tensor<T>::urandom(int limit) {
    for (auto i = 0u; i < size_[0]; ++i) {
        for (auto j = 0u; j < size_[1]; ++j) {
            for (auto k = 0u; k < size_[2]; ++k) {
                data_[i][j][k] = rand() % limit;
            }
        }
    }
}


// Functions to print a Tensor
template <class T> 
void Tensor<T>::print(std::ostream &s) const {
    s << "[";
    for (auto i = 0u; i < size_[0]; ++i) {
        s << "[";
        for (auto j = 0u; j < size_[1]; ++j) {
            s << "[";
            for (auto k = 0u; k < size_[2]; ++k) {
                s << data_[i][j][k] << ", ";
            }
            s << "\b\b], ";
        }
        s << "\b\b], ";
        if (i != size_[0] - 1)
            s << std::endl << " ";
    }
    s << "\b\b]"; 
}

template <class T> 
std::ostream &operator<<(std::ostream &s, const Tensor<T> &t) {
    t.print(s);
    return s;
}


// int main(int argc, char *argv[]) {

//     Tensor<float> t(4, 2, 3);
//     t.urandom();
//     std::cout << t << std::endl;


//     return 0;
// }