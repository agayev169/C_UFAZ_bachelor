#ifndef __TRIANGLE_C__
#define __TRIANGLE_C__

#include <math.h>
#include "position.c"

typedef struct Triangle {
    SPos pos;
    float length;
    int color;
} STriangle;

float trianglePerimeter(STriangle tr) {
    return 3 * tr.length;
}

float triangleArea(STriangle tr) {
    return tr.length * sqrt(3) * tr.length / 4.0; 
}

#endif