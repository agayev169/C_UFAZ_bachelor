#ifndef __POSITION_CPP__
#define __POSITION_CPP__

class CPos {
    float x_;
    float y_;
public:
    CPos(int x, int y): x_(x), y_(y) {}

    float getX() {return x_;}

    float getY() {return y_;}
};

#endif