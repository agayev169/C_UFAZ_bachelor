#include "conv.hpp"

Conv::Conv(unsigned int steps, unsigned int a, unsigned int b, unsigned int c): 
    conv_(steps, Tensor<int>(a, b, c)), pos_(steps) {}

Conv::Conv(unsigned int steps, const std::vector<unsigned int> &size):
    conv_(steps, Tensor<int>(size)), pos_(steps) {}

Conv::Conv(const std::vector<Tensor<int>> &conv, unsigned int steps):
    conv_(conv), pos_(steps) {}

Conv::Conv(const Conv &c): 
    conv_(c.conv_), pos_(c.pos_) {}

std::vector<std::pair<unsigned int, unsigned int>> Conv::getPos() const {
    return pos_;
}

void Conv::findMaxSTD(const BMPImage &img) {
    for (auto h = 0u; h < conv_.size(); ++h) {
        findMaxSTD(img, h, img.getWidth() / 2);
    }
}

void Conv::findMaxSTD(const BMPImage &img, unsigned int h, int minX, int maxX) {
    if (h >= conv_.size()) return;
    maxX = (maxX == -1) ? img.getWidth() : maxX;
    double maxSTD = 0;
    unsigned int stepSize = img.getHeight() / conv_.size();
    for (auto y = h * stepSize; y < (h + 1) * stepSize - conv_[h].getSize()[0]; ++y) {
        for (auto x = (unsigned int) minX; x < (unsigned int) maxX - conv_[h].getSize()[1]; ++x) {
            Tensor<int> curVals(conv_[h].getSize());
            for (auto y_ = y; y_ < y + conv_[h].getSize()[0]; ++y_) {
                for (auto x_ = x; x_ < x + conv_[h].getSize()[1]; ++x_) {
                    for (auto z_ = 0u; z_ < conv_[h].getSize()[2]; ++z_) {
                        curVals.data_[y_ - y][x_ - x][z_] = 
                            img.pixels_[((y_ * img.getWidth()) + x_) * img.getBytesPerPixel() + z_];
                    }
                }
            }
            double curSTD = curVals.std();
            if (curSTD >= maxSTD) {
                maxSTD = curSTD;
                conv_[h] = curVals;
                pos_[h].first = x;
                pos_[h].second = y;
            }
        }
    }
    for (auto y = pos_[h].second; y < pos_[h].second + conv_[h].getSize()[0]; ++y) {
        for (auto x = pos_[h].first; x < pos_[h].first + conv_[h].getSize()[1]; ++x) {
            for (auto z = 0u; z < conv_[h].getSize()[2]; ++z) {
                img.pixels_[(y * img.getWidth() + x) * img.getBytesPerPixel() + z] =
                    255 - img.pixels_[(y * img.getWidth() + x) * img.getBytesPerPixel() + z];
            }
        }
    }
}

Conv Conv::findSimilar(const BMPImage &img) const {
    Conv result(conv_.size(), conv_[0].getSize()[0], 
        conv_[0].getSize()[1], conv_[0].getSize()[2]);
    // std::cout << "Finding similar of:" << std::endl;
    // for (auto i = 0u; i < pos_.size(); ++i) {
    //     std::cout << pos_[i].first << " " << pos_[i].second << std::endl;
    // }
    unsigned int stepSize = img.getHeight() / conv_.size();
    for (auto h = 0u; h < conv_.size(); ++h) {
        double minDiff = 10e10;
        unsigned int maxX = 0;
        for (auto y = (unsigned int) std::max(0, (int) pos_[h].second - 20); 
            y < pos_[h].second + 20 - conv_[h].getSize()[0] && 
            y < img.getHeight() - conv_[h].getSize()[0]; ++y) {
            for (auto x = 0u; x < (unsigned int) pos_[h].first - conv_[h].getSize()[1]; ++x) {
                Tensor<int> curVals(conv_[h].getSize());
                for (auto y_ = y; y_ < y + conv_[h].getSize()[0]; ++y_) {
                    for (auto x_ = x; x_ < x + conv_[h].getSize()[1]; ++x_) {
                        for (auto z_ = 0u; z_ < conv_[h].getSize()[2]; ++z_) {
                            curVals.data_[y_ - y][x_ - x][z_] = 
                                img.pixels_[((y_ * img.getWidth()) + x_) * img.getBytesPerPixel() + z_];
                        }
                    }
                }
                // Tensor<int> diff = conv_[h] - curVals;
                // for (auto i = 0u; i < diff.getSize()[0]; ++i) {                    
                //     for (auto j = 0u; j < diff.getSize()[1]; ++j) {                    
                //         for (auto k = 0u; k < diff.getSize()[2]; ++k) {                    
                //             diff.data_[i][j][k] = abs(diff.data_[i][j][k]);
                //         }
                //     }
                // }
                // double difference = diff.std() + abs(diff.mean());
                double difference = curVals.dist(conv_[h]);
                if (difference < minDiff || (difference == minDiff && maxX < x)) {
                    minDiff = difference;
                    result.conv_[h] = curVals;
                    result.pos_[h].first = x;
                    result.pos_[h].second = y;
                    maxX = x;
                }
            }
        }

        for (auto y = result.pos_[h].second; y < result.pos_[h].second + conv_[h].getSize()[0]; ++y) {
            for (auto x = result.pos_[h].first; x < result.pos_[h].first + conv_[h].getSize()[1]; ++x) {
                for (auto z = 0u; z < conv_[h].getSize()[2]; ++z) {
                    img.pixels_[(y * img.getWidth() + x) * img.getBytesPerPixel() + z] =
                        255 - img.pixels_[(y * img.getWidth() + x) * img.getBytesPerPixel() + z];
                }
            }
        }
    }
    return result;
}