#include "marker.hpp"

// Constructor
Marker::Marker(unsigned int steps, unsigned int a, unsigned int b, unsigned int c): 
    data_(steps, Tensor<int>(a, b, c)), pos_(steps) {}

Marker::Marker(unsigned int steps, const std::vector<unsigned int> &size):
    data_(steps, Tensor<int>(size)), pos_(steps) {}

Marker::Marker(const std::vector<Tensor<int>> &conv, unsigned int steps):
    data_(conv), pos_(steps) {}

// Copy constructor
Marker::Marker(const Marker &c): 
    data_(c.data_), pos_(c.pos_) {}

std::vector<std::pair<unsigned int, unsigned int>> Marker::getPos() const {
    return pos_;
}

// Function to find the most distinguishable spots on an image
void Marker::findMaxSTD(const BMPImage &img) {
    for (auto h = 0u; h < data_.size(); ++h) {
        // Find the areas in the right side so that they appear on the next image for sure
        findMaxSTD(img, h, img.getWidth() / 2); 
    }
}

// Function to find the most distinguishable spot on a certain height of an image
void Marker::findMaxSTD(const BMPImage &img, unsigned int h, int minX, int maxX) {
    if (h >= data_.size()) return; // In case of any error return (Actually, that's not going to happen)
    maxX = (maxX == -1) ? img.getWidth() : maxX; // If maxX = the default value (-1) then assign it to the width
    double maxSTD = 0; // Max STD found untill a certain iteration 
    unsigned int stepSize = img.getHeight() / data_.size(); // Height to be covered
    // Values of y and x are restricted for the case of them going beyond boundaries
    for (auto y = h * stepSize; y < (h + 1) * stepSize - data_[h].getSize()[0]; ++y) {
        for (auto x = (unsigned int) minX; x < (unsigned int) maxX - data_[h].getSize()[1]; ++x) {
            Tensor<int> curVals(data_[h].getSize()); // Current spot
            for (auto y_ = y; y_ < y + data_[h].getSize()[0]; ++y_) {
                for (auto x_ = x; x_ < x + data_[h].getSize()[1]; ++x_) {
                    for (auto z_ = 0u; z_ < data_[h].getSize()[2]; ++z_) {
                        curVals.data_[y_ - y][x_ - x][z_] = 
                            img.pixels_[((y_ * img.getWidth()) + x_) * img.getBytesPerPixel() + z_];
                    }
                }
            }

            double curSTD = curVals.std(); // Current STD
            if (curSTD >= maxSTD) { // If this spot is more distinguishable then save it
                maxSTD = curSTD;
                data_[h] = curVals;
                pos_[h].first = x;
                pos_[h].second = y;
            }
        }
    }
}

Marker Marker::findSimilar(const BMPImage &img) const {
    Marker result(data_.size(), data_[0].getSize()[0], 
        data_[0].getSize()[1], data_[0].getSize()[2]); // New marker
    for (auto h = 0u; h < data_.size(); ++h) {
        double minDiff = 10e10; // A HUGE value so that there is a smaller value definitely
        unsigned int minDiffX = 0;
        for (auto y = (unsigned int) std::max(0, (int) pos_[h].second - 20); 
            y < pos_[h].second + 20 - data_[h].getSize()[0] && 
            y < img.getHeight() - data_[h].getSize()[0]; ++y) {
            for (auto x = 0u; x < (unsigned int) pos_[h].first - data_[h].getSize()[1]; ++x) {
                Tensor<int> curVals(data_[h].getSize()); // Current spot
                for (auto y_ = y; y_ < y + data_[h].getSize()[0]; ++y_) {
                    for (auto x_ = x; x_ < x + data_[h].getSize()[1]; ++x_) {
                        for (auto z_ = 0u; z_ < data_[h].getSize()[2]; ++z_) {
                            curVals.data_[y_ - y][x_ - x][z_] = 
                                img.pixels_[((y_ * img.getWidth()) + x_) * img.getBytesPerPixel() + z_];
                        }
                    }
                }

                double difference = curVals.dist(data_[h]); // Distance
                if (difference < minDiff || (difference == minDiff && minDiffX < x)) {
                    // In case of distance being less than the smallest for the iteration
                    // or being the same but more to the right
                    minDiff = difference;
                    result.data_[h] = curVals;
                    result.pos_[h].first = x;
                    result.pos_[h].second = y;
                    minDiffX = x;
                }
            }
        }
    }
    return result;
}
