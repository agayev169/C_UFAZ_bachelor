#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include "math.h"

int const winWidth = 400, winHeight = 400;
int const winFar = 600;
float angle = 0.0f;
float scale = 1.0f;

void timer(int);
void display ();
void initialize ();
void drawPoint (float x, float y);

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First");
    initialize();
    glutTimerFunc(50, timer, 0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void timer (int smth) {
    ++angle;
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    scale = 1.0 - abs(sin(3.1415926*angle/90.0)/sqrt(3.0)/2);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scale, scale, 1.0);
    glBegin(GL_LINES);
        for (float i = -winWidth/2; i <= winWidth/2; i+=20.0f) {
            glVertex2f(i, -winHeight/2);
            glVertex2f(i, winHeight/2);
        }
        for (float i = -winHeight/2; i <= winHeight/2; i+=20.0f) {
            glVertex2f(-winWidth/2, i);
            glVertex2f(winWidth/2, i);
        }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void initialize () {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-winWidth/2, winWidth/2, -winHeight/2, winHeight/2, -winFar/2, winFar/2);
    glMatrixMode(GL_MODELVIEW);
}

void drawPoint (float x, float y) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}
