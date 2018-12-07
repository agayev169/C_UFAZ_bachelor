#include "position.cpp"
#include <math.h>

class CTriangle {
    CPos pos_;
    int color_;
    float length_;
public:
    CTriangle(float length, int color, CPos pos):
        pos_(pos), color_(color), length_(length) {};

    float perimeter() {return 3 * length_;}

    float surface() {return length_ * sqrt(3) * length_ / 4;}
};