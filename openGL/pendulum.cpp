#include "GL/glut.h"
#include "GL/gl.h"
#include <math.h>
#include <iostream>

struct Particle {
        float x, y, vx, vy, r, ax, ay;
};

Particle p;

void display();
void timer(int);

int main(int argc, char *argv[]) {

    p.x = 640 / 2;
    p.y = 280;
    p.vx = 5;
    p.vy = 0;
    p.r = 10;
    p.ax = 0;
    p.ay = 0;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Pendulum");
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}

void timer(int = 0) {
    display();
    float d = sqrt((p.x - 640 / 2) * (p.x - 640 / 2) + (p.y - 0) * (p.y - 0));

    if (p.x == 640 / 2) p.ay = 0;

    p.ax = 0.1 * (-9.81 * (p.x - 640 / 2) / d);
    p.ay = 0.1 * ((9.81 * (p.y  - 0) / d + 9.81 * (p.x - 640 / 2) / d) - 9.81 * (p.y  - 0) / d);

    // p.vy += 9.81 - 9.81 * (p.y  - 0) / d;
    // p.vx -= 9.81 * (p.x - 640 / 2) / d;
    p.vx += p.ax;
    p.vy += p.ay;

    p.x += p.vx;
    p.y += p.vy;
    glutTimerFunc(10, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //Particle
    glBegin(GL_LINES);
    glVertex2f(640 / 2, 0);
    glVertex2f(p.x, p.y);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 36; i++) {
        glVertex2f(p.x + p.r * cos ((i) * 2 * M_PI / 36), p.y + p.r * sin ((i) * 2 * M_PI / 36));
        glVertex2f(p.x + p.r * cos ((i + 1) * 2 * M_PI / 36), p.y + p.r * sin ((i + 1) * 2 * M_PI / 36));
    }
    glEnd();
    glutSwapBuffers();
}
