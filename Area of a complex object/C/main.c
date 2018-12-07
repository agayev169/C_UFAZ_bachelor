#include <stdio.h>
#include "sketchMan.c"

int main(int argc, char *argv[]) {
    SSketchMan man;
    man.arms[0] = (SRectangle) {{0, 0}, 20, 20, 20};
    man.arms[1] = (SRectangle) {{0, 0}, 20, 20, 20};
    man.legs[0] = (SRectangle) {{0, 0}, 20, 20, 20};
    man.legs[1] = (SRectangle) {{0, 0}, 20, 20, 20};
    man.torso = (SRectangle) {{0, 0}, 0, 20, 20};
    man.head = (SCircle) {{0, 0}, 20, 20};
    man.hat = (STriangle) {{0, 0}, 20, 20};

    printf("%f\n", SketchManPerimeter(man));
    printf("%f\n", SketchManArea(man));

    return 0;
}
