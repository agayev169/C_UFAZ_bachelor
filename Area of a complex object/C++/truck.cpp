#include <iostream>
#include "circle.cpp"
#include "triangle.cpp"
#include "rectangle.cpp"

class CTruck {
    CRectangle body_[3];
    CTriangle glass_;
    CCircle wheel_[6];
public:
    CTruck(CRectangle body1, CRectangle body2, CRectangle body3,
        CTriangle glass, CCircle wheel1, CCircle wheel2,
        CCircle wheel3, CCircle wheel4, CCircle wheel5,
        CCircle wheel6): body_{body1, body2, body3}, 
        glass_(glass), wheel_{wheel1, wheel2, wheel3,
        wheel4, wheel5, wheel6} {}

    float perimeter() {
        float p = 0;
        for (int i = 0; i < 3; i++) {
            p += body_[i].perimeter();
        }
        p += glass_.perimeter();
        for (int i = 0; i < 6; i++) {
            p += wheel_[i].perimeter();
        }
        return p;
    }

    float surface() {
        float s = 0;
        for (int i = 0; i < 3; i++) {
            s += body_[i].surface();
        }
        s += glass_.surface();
        for (int i = 0; i < 6; i++) {
            s += wheel_[i].surface();
        }
        return s;
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    CRectangle body1(10, 10, 1, CPos(1, 1));
    CRectangle body2(10, 10, 1, CPos(1, 1));
    CRectangle body3(10, 10, 1, CPos(1, 1));
    CTriangle glass(10, 1, CPos(1, 1));
    CCircle wheel1(10, 1, CPos(1, 1));
    CCircle wheel2(10, 1, CPos(1, 1));
    CCircle wheel3(10, 1, CPos(1, 1));
    CCircle wheel4(10, 1, CPos(1, 1));
    CCircle wheel5(10, 1, CPos(1, 1));
    CCircle wheel6(10, 1, CPos(1, 1));

    CTruck truck = CTruck(body1,body2, body3, glass, wheel1, wheel2, 
        wheel3, wheel4, wheel5, wheel6);

    cout << "Perimeter: " << truck.perimeter() << endl;
    cout << "Surface: " << truck.surface() << endl;

    return 0;
}
