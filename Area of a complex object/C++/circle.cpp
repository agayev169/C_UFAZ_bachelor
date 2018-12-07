#include "position.cpp"
#include <math.h>

class CCircle {
    CPos pos_;
    int color_;
    float radius_;
public:
    CCircle(float radius, int color, CPos pos):
        pos_(pos), color_(color), radius_(radius) {};

    float perimeter() {return 2 * radius_ * M_PI;}

    float surface() {return M_PI * radius_ * radius_;}
};