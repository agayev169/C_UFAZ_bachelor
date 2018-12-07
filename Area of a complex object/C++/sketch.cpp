#include <iostream>
#include "circle.cpp"
#include "triangle.cpp"
#include "rectangle.cpp"

class CSketchMan {
    CRectangle arm_[2];
    CRectangle leg_[2];
    CRectangle torso_;
    CCircle head_;
    CTriangle hat_;
public:
    CSketchMan(CRectangle arm1, CRectangle arm2, 
        CRectangle leg1, CRectangle leg2, CRectangle torso,
        CCircle head, CTriangle hat): arm_{arm1, arm2}, 
        leg_{leg1, leg2}, torso_(torso), head_(head), hat_(hat) {}

    float perimeter() {
        return arm_[0].perimeter() + arm_[1].perimeter() +
            leg_[0].perimeter() + leg_[1].perimeter() + 
            torso_.perimeter() + head_.perimeter() + 
            hat_.perimeter();
    }

    float surface() {
        return arm_[0].surface() + arm_[1].surface() +
            leg_[0].surface() + leg_[1].surface() + 
            torso_.surface() + head_.surface() + 
            hat_.surface();
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    CRectangle arm1(10, 10, 1, CPos(1, 1));
    CRectangle arm2(10, 10, 1, CPos(1, 1));
    CRectangle leg1(10, 10, 1, CPos(1, 1));
    CRectangle leg2(10, 10, 1, CPos(1, 1));
    CRectangle torso(10, 10, 1, CPos(1, 1));
    CCircle head(10, 1, CPos(1, 1));
    CTriangle hat(10, 1, CPos(1, 1));

    CSketchMan skMan(arm1, arm2, leg1, leg2, torso, head, hat);

    cout << "Perimeter: " << skMan.perimeter() << endl;
    cout << "Surface: " << skMan.surface() << endl;

    return 0;
}
