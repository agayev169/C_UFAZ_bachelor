#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int const winWidth = 400, winHeight = 400;
int const winFar = 50;

typedef struct {
    double vx;
    double vy;
    double x;
    double y;
    double m;
    float r;
} Object;

    Object objs[5];

void drawObj(Object obj);
void timer(int);
void display ();
void initialize ();

int main(int argc, char *argv[]) {


    //0-Sun, 1-Mercury, 2-Venerus, 3-Earth, 4-Moon
    //Distance prooportion = 384400
    //Mass prooportion = 7,3477×10²²

    objs[0].x = 200;
    objs[0].y = 200;
    objs[0].vx = 0;
    objs[0].vy = 0;
    objs[0].m = 27069695;
    objs[0].r = 1.809*10;

    objs[1].x = 200 + 150.6503 / 2;
    objs[1].y = 200;
    objs[1].vx = 0;
    objs[1].vy = 1.35;
    objs[1].m = 4.47078;
    objs[1].r = 0.006347555*100;

    objs[2].x = 200 + 281.4776 / 2;
    objs[2].y = 200;
    objs[2].vx = 0;
    objs[2].vy = 1.1;
    objs[2].m = 66.2384;
    objs[2].r = 0.015744017*100;

    objs[3].x = 200 + 389.1779 / 2;
    objs[3].y = 200;
    objs[3].vx = 0;
    objs[3].vy = .9;
    objs[3].m = 81.2771;
    objs[3].r = 0.016573881*100;

    objs[4].x = 200 + 390.1779 / 2;
    objs[4].y = 200;
    objs[4].vx = 0;
    objs[4].vy = .93;
    objs[4].m = 1;
    objs[4].r = 0.00451873*100;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First");
    initialize();
    glutTimerFunc(1, timer, 0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void timer (int) {
    glutPostRedisplay();
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            float d = sqrt((objs[j].x - objs[i].x) * (objs[j].x - objs[i].x) + (objs[j].y - objs[i].y) * (objs[j].y - objs[i].y));
            if (d > 3) {
                // printf("%f\n", 6.67 / 1000 * objs[j].m / d / d * (objs[j].x - objs[i].x) / d);
                objs[i].vx += 6.67 / 1000000 * objs[j].m / d / d * (objs[j].x - objs[i].x) / d;
                objs[i].vy += 6.67 / 1000000 * objs[j].m / d / d * (objs[j].y - objs[i].y) / d;
            }
        }
        objs[i].x += objs[i].vx;
        // printf("%f\n", objs[4].x);
        objs[i].y += objs[i].vy;
    }
    glutTimerFunc(1, timer, 0);
}

void drawObj(Object obj) {
    glBegin(GL_POINTS);
    for (float j = 0; j < obj.r; j+=0.1) {
        for (float i = 0; i <  M_PI * j; i+=0.1) {
            glVertex2f(obj.x + j * cos(i), obj.y + j * sin(i));
        }
    }
    glEnd();
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(0.8f, 0.8f, 0.0f);
    // printf("%f %f\n", objs[0].x, objs[0].y);
    // glVertex2f(objs[0].x, objs[0].y);
    drawObj(objs[0]);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glutSolidSphere(objs[0].r, 20, 20);
    glColor3f(0.5f, 0.5f, 0.5f);
    // glVertex2f(objs[1].x, objs[1].y);
    drawObj(objs[1]);
    glColor3f(0.6f, 0.6f, 0.2f);
    drawObj(objs[2]);
    // glVertex2f(objs[2].x, objs[2].y);
    glColor3f(0.0f, 1.0/191, 1.0f);
    drawObj(objs[3]);
    // glVertex2f(objs[3].x, objs[3].y);
    // glColor3f(0.6f, 0.6f, 0.2f);
    // glVertex2f(objs[4].x, objs[4].y);
    glEnd();
    glutSwapBuffers();
}

void initialize () {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -winFar/2, winFar/2);
    glMatrixMode(GL_MODELVIEW);
}
