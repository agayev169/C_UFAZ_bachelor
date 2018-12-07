#ifndef __CIRCLE_C__
#define __CIRCLE_C__

#include "position.c"

typedef struct Circle {
    SPos center;
    float r;
    int color;
} SCircle;

float circlePerimeter(SCircle circ) {
    return 2 * 3.1415926535 * circ.r; 
}

float circleArea(SCircle circ) {
    return 3.1415926535 * circ.r * circ.r; 
}

#endif