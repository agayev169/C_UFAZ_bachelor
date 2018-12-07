#ifndef __RECTANGLE_C__
#define __RECTANGLE_C__

#include "position.c"

typedef struct Rectangle {
    SPos pos;
    float width, height;
    int color;
} SRectangle;

float rectanglePerimeter(SRectangle rect) {
    return (rect.width + rect.height) * 2; 
}

float rectangleArea(SRectangle rect) {
    return rect.width * rect.height; 
}

#endif