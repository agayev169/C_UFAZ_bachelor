#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

const int winWidth = 640;
const int winHeight = 480;

void display();

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pareto front");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE);
    glVertex2f(100, winHeight - 100);
    glVertex2f(winWidth - 100, winHeight - 100);
    glEnd();
}