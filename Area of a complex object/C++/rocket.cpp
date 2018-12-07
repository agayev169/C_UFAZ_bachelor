#include <iostream>
#include "circle.cpp"
#include "triangle.cpp"
#include "rectangle.cpp"

class CRocket {
    CRectangle body_[3];
    CTriangle body_head[3];
    CTriangle turbine_[3];
public:
    CRocket(CRectangle body1, CRectangle body2, CRectangle body3,
        CTriangle body_head1, CTriangle body_head2, CTriangle body_head3,
        CTriangle turbine1, CTriangle turbine2, CTriangle turbine3):
        body_{body1, body2, body3}, 
        body_head{body_head1, body_head2, body_head3},
        turbine_{turbine1, turbine2, turbine3} {}

    float perimeter() {
        float p = 0;
        for (int i = 0; i < 3; i++) {
            p += body_[i].perimeter();
            p += body_head[i].perimeter();
            p += turbine_[i].perimeter();
        }
        return p;
    }

    float surface() {
        float s = 0;
        for (int i = 0; i < 3; i++) {
            s += body_[i].surface();
            s += body_head[i].surface();
            s += turbine_[i].surface();
        }
        return s;
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    CRectangle body1(10, 10, 1, CPos(1, 1));
    CRectangle body2(10, 10, 1, CPos(1, 1));
    CRectangle body3(10, 10, 1, CPos(1, 1));
    CTriangle body_head1(10, 1, CPos(1, 1));
    CTriangle body_head2(10, 1, CPos(1, 1));
    CTriangle body_head3(10, 1, CPos(1, 1));
    CTriangle turbine1(10, 1, CPos(1, 1));
    CTriangle turbine2(10, 1, CPos(1, 1));
    CTriangle turbine3(10, 1, CPos(1, 1));
    CRocket rocket = CRocket(body1, body2, body3,
        body_head1, body_head2, body_head3, turbine1,
        turbine2, turbine3);

    cout << "Perimeter: " << rocket.perimeter() << endl;
    cout << "Surface: " << rocket.surface() << endl;

    return 0;
}
