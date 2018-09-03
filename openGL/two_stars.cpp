#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int const winWidth = 800, winHeight = 800;
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


    //0-Star #!, 1-Star #2, 2-Planet
    //Distance prooportion ~ 6000
    //Mass prooportion = 7,3477×10²²

    objs[0].x = 200;
    objs[0].y = winHeight/2;
    objs[0].vx = 0;
    objs[0].vy = 0;
    objs[0].m = 210;
    objs[0].r = 20;

    objs[1].x = 600;
    objs[1].y = winHeight/2;
    objs[1].vx = 0;
    objs[1].vy = 0;
    objs[1].m = 260;
    objs[1].r = 20*260/210;

    objs[2].x = 160;
    objs[2].y = winHeight/2;
    objs[2].vx = 0;
    objs[2].vy = 1.2;
    objs[2].m = 0.0006312896;
    objs[2].r = 1;

    // objs[3].x = 95;
    // objs[3].y = winHeight/2;
    // objs[3].vx = 0;
    // objs[3].vy = .5;
    // objs[3].m = 0.0005312896;
    // objs[3].r = 1;
    //
    // objs[4].x = 110;
    // objs[4].y = winHeight/2;
    // objs[4].vx = 0;
    // objs[4].vy = .8;
    // objs[4].m = 0.0007312896;
    // objs[4].r = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Two stars and planet");
    initialize();
    glutTimerFunc(1, timer, 0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void timer (int) {
    glutPostRedisplay();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i == 0 && j == 1) || (i == 1 && j == 0)) continue;
            if (i == j) continue;
            float d = sqrt((objs[j].x - objs[i].x) * (objs[j].x - objs[i].x) + (objs[j].y - objs[i].y) * (objs[j].y - objs[i].y));
            if (d > .5) {
                objs[i].vx += 6.67 / 25 * objs[j].m / d / d * (objs[j].x - objs[i].x) / d;
                objs[i].vy += 6.67 / 25 * objs[j].m / d / d * (objs[j].y - objs[i].y) / d;
            }
        }
        objs[i].x += objs[i].vx;
        // printf("%f\n", objs[2].vx);
        objs[i].y += objs[i].vy;
    }
    glutTimerFunc(1, timer, 0);
}

void drawObj(Object obj) {
    glBegin(GL_POINTS);
    for (float j = 0; j < obj.r; j+=0.2) {
        for (float i = 0; i <  M_PI * j; i+=0.2) {
            glVertex2f(obj.x + j * cos(i), obj.y + j * sin(i));
        }
    }
    glEnd();
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(0.8f, 0.8f, 0.0f);
    drawObj(objs[0]);
    glColor3f(0.8f, 0.8f, 0.0f);
    drawObj(objs[1]);
    glColor3f(0.0f, 1.0/191, 1.0f);
    drawObj(objs[2]);
    // glPointSize(50);
    // glVertex2f(objs[2].x, objs[2].y);
    // glVertex2f(200, 700);
    // glPointSize(1);
    // drawObj(objs[3]);
    // drawObj(objs[4]);

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
