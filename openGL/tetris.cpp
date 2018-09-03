#include "GL/glut.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RED 0
#define BLUE 1
#define YELLOW 2
#define GREEN 3
#define ORANGE 4

bool blocks[10][21];

int const dr = 20;

class Tetramino {
public:
    unsigned char dest;
    unsigned char color;
    float x, y, rx, ry;
    Tetramino() {
        srand(time(NULL));

        dest = 0;
        color = rand() % 5;
        x = 11;
        y = 2;
    }

    void draw() {
        if (color == RED) {
            glColor3f(1, 0, 0);
            if (dest == 0) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x) * dr, (y + 1) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 2) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glEnd();
            } else
            if (dest == 1) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y + 3) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
            } else
            if (dest == 2) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x + 3) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
            } else
            if (dest == 3) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glVertex2f((x) * dr, (y + 3) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 2) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glEnd();
            }
        } else if (color == BLUE) {
            glColor3f(0, 0, 1);
            if (dest == 0) {
                rx = x + 4;
                ry = y + 1;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 4) * dr, (y) * dr);
                glVertex2f((x + 4) * dr, (y + 1) * dr);
                glVertex2f((x) * dr, (y + 1) * dr);
                glEnd();
            } else
            if (dest == 1) {
                rx = x + 1;
                ry = y + 4;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 4) * dr);
                glVertex2f((x) * dr, (y + 4) * dr);
                glEnd();
            }
            if (dest == 2) {
                rx = x + 4;
                ry = y + 1;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 4) * dr, (y) * dr);
                glVertex2f((x + 4) * dr, (y + 1) * dr);
                glVertex2f((x) * dr, (y + 1) * dr);
                glEnd();
            } else
            if (dest == 3) {
                rx = x + 1;
                ry = y + 4;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 4) * dr);
                glVertex2f((x) * dr, (y + 4) * dr);
                glEnd();
            }
        } else if (color == YELLOW) {
            rx = x + 2;
            ry = y + 2;
            glColor3f(1, 1, 0);
            glBegin(GL_QUADS);
            glVertex2f((x) * dr, (y) * dr);
            glVertex2f((x + 2) * dr, (y) * dr);
            glVertex2f((x + 2) * dr, (y + 2) * dr);
            glVertex2f((x) * dr, (y + 2) * dr);
            glEnd();
        } else if (color == GREEN) {
            glColor3f(0.2, 0.8, 0.2);
            if (dest == 0) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 3) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glEnd();
            } else
            if (dest == 1) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glEnd();
            } else
            if (dest == 2) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 3) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glEnd();
            } else
            if (dest == 3) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glEnd();
            }
        } else if (color == ORANGE) {
            glColor3f(1, 0.647, 0);
            if (dest == 0) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glVertex2f((x) * dr, (y + 3) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glVertex2f((x + 2) * dr, (y + 2) * dr);
                glVertex2f((x + 2) * dr, (y + 3) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glEnd();
            } else
            if (dest == 1) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x) * dr, (y + 1) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x + 1) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
            } else
            if (dest == 2) {
                rx = x + 2;
                ry = y + 3;
                glBegin(GL_QUADS);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y) * dr);
                glVertex2f((x + 2) * dr, (y + 3) * dr);
                glVertex2f((x + 1) * dr, (y + 3) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y) * dr);
                glVertex2f((x + 1) * dr, (y + 1) * dr);
                glVertex2f((x) * dr, (y + 1) * dr);
                glEnd();
            } else
            if (dest == 3) {
                rx = x + 3;
                ry = y + 2;
                glBegin(GL_QUADS);
                glVertex2f((x) * dr, (y + 1) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x + 3) * dr, (y + 2) * dr);
                glVertex2f((x) * dr, (y + 2) * dr);
                glEnd();
                glBegin(GL_QUADS);
                glVertex2f((x + 2) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y) * dr);
                glVertex2f((x + 3) * dr, (y + 1) * dr);
                glVertex2f((x + 2) * dr, (y + 1) * dr);
                glEnd();
            }
        }
    }
};

Tetramino t, next;

void display();
void timer(int = 0);
void keyboard(unsigned char k, int x, int y);

int main(int argc, char *argv[]) {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            blocks[x][y] = false;
        }
    }
    for (int x = 0; x < 10; x++) {
        blocks[x][20] = true;
    }
    srand(time(NULL));
    t.x = 3;
    t.y = 0;
    next.color = rand() % 5;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(320, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Classic Snake");
    glutInitDisplayMode(GL_PROJECTION);
    glOrtho(0, 320, 400, 0, -1, 1);
    glutInitDisplayMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    timer();
    glutMainLoop();

    return 0;
}

void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case 'a':
            if (t.x > 0)
                t.x--;
            break;
        case 'd':
            if (t.rx < 10)
                t.x++;
            break;
        case 'e':
            t.dest = (t.dest + 1) % 4;
            break;
        case 'q':
            t.dest = abs(t.dest - 1) % 4;
            break;
        case 's':
            t.y += 1.0/3;
            break;
    }
}

void timer(int) {
    display();
    t.y += 1.0/20;
    // if()
    glutTimerFunc(10, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //Grid
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            glVertex2f(x * dr, y * dr);
        }
    }
    glEnd();
    //Boundary
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(10 * dr, 0);
    glVertex2f(10 * dr, 20 * dr);
    glEnd();
    //Next
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(10.5 * dr, 1.5 * dr);
    glVertex2f(15.5 * dr, 1.5 * dr);
    glVertex2f(15.5 * dr, 6.5 * dr);
    glVertex2f(10.5 * dr, 6.5 * dr);
    glVertex2f(10.5 * dr, 1.5 * dr);
    glEnd();
    t.draw();
    next.draw();
    glutSwapBuffers();
}
