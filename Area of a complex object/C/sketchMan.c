#include "rectangle.c"
#include "triangle.c"
#include "circle.c"

typedef struct SketchMan {
    SRectangle arms[2], legs[2], torso;
    SCircle head;
    STriangle hat;
} SSketchMan;

float SketchManPerimeter(SSketchMan man) {
    float res = 0.0;
    res += rectanglePerimeter(man.arms[0]);
    res += rectanglePerimeter(man.arms[1]);
    res += rectanglePerimeter(man.legs[0]);
    res += rectanglePerimeter(man.legs[1]);
    res += rectanglePerimeter(man.torso);
    res += circlePerimeter(man.head);
    res += trianglePerimeter(man.hat);
    return res;
} 

float SketchManArea(SSketchMan man) {
    float res = 0.0;
    res += rectangleArea(man.arms[0]);
    res += rectangleArea(man.arms[1]);
    res += rectangleArea(man.legs[0]);
    res += rectangleArea(man.legs[1]);
    res += rectangleArea(man.torso);
    res += circleArea(man.head);
    res += triangleArea(man.hat);
    return res;
} 