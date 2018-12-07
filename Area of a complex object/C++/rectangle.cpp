#include "position.cpp"

class CRectangle {
    CPos pos_;
    int color_;
    float width_;
    float height_;
public:
    CRectangle(float width, float height, int color, CPos pos):
        pos_(pos), color_(color), width_(width), height_(height) {};

    float perimeter() {return 2 * (width_ + height_);}

    float surface() {return width_ * height_;}

    CPos *cogPos() {
        CPos *cogPos_ = new CPos(pos_.getX() + width_ / 2, pos_.getY() + height_ / 2);
        return cogPos_;
    }
};