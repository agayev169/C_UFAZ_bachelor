#include "GL/glut.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Particle {
    float x, y, vx, vy, r;
};

struct v2 {
    float x,y;
};

struct Path {
    struct v2 v2[100];
    int next;
};

int const N = 400;//Number of elements
// int const R = 5;//Radius
float const C = 2.1;//Magnitude of velocity

Particle p[N];

float sqr (float x);
void display();
void drawParticle(Particle p);
void timer(int);
void timer2(int);

Path path;

int main(int argc, char *argv[]) {
    path.next = 0;
    for (int i = 0; i < 100; i++) {
        path.v2[i].x = -1;
        path.v2[i].y = -1;
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        p[i].x = rand() % 640;
        p[i].y = rand() % 480;
        float angle = rand() * 7;
        p[i].vx = C * cos(angle);
        p[i].vy = C * sin(angle);
        p[i].r = rand() % 3 + 1;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Brownian Motion");
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    timer(0);
    timer2(0);
    glutMainLoop();

    return 0;
}

void timer2(int = 0) {
    path.v2[path.next].x = p[0].x;
    path.v2[path.next].y = p[0].y;
    (++path.next) %= 100;
    glutTimerFunc(1, timer2, 0);
}

void timer(int = 0) {
    display();
    for (int i = 0; i < N; i++) {
        // if (p[i].x <= 0 && p[i].vx < 0) p[i].x += 640;
        // if (p[i].x >= 640 && p[i].vx > 0) p[i].x -= 640;
        // if (p[i].y <= 0 && p[i].vy < 0) p[i].y += 480;
        // if (p[i].y >= 480 && p[i].vy > 0) p[i].y -= 480;


        if (p[i].x <= 0 && p[i].vx < 0) {p[i].vx *= -1;p[i].x = 0.01;}
        if (p[i].x >= 640 && p[i].vx > 0) {p[i].vx *= -1;p[i].x = 639.99;}
        if (p[i].y <= 0 && p[i].vy < 0) {p[i].vy *= -1;p[i].y = 0.01;}
        if (p[i].y >= 480 && p[i].vy > 0) {p[i].vy *= -1;p[i].y = 479.99;}

        for (int j = 0; j < N; j++) {
            if(i != j) {
                float d = sqrt(sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y));
                if (d <= p[i].r + p[j].r)  {
                    float f = p[i].r + p[j].r - d;
                    p[i].vx += f * (p[i].x - p[j].x) / d / sqr(p[i].r);
                    p[i].vy += f * (p[i].y - p[j].y) / d / sqr(p[i].r);

                    p[j].vx -= f * (p[i].x - p[j].x) / d / sqr(p[j].r);
                    p[j].vy -= f * (p[i].y - p[j].y) / d / sqr(p[j].r);
                }
            }
        }

        p[i].x += p[i].vx;
        p[i].y += p[i].vy;
    }
    glutTimerFunc(1, timer, 0);
}

void drawParticle(Particle p) {
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 36; i++) {
        glVertex2f(p.x + p.r * cos(i * M_PI * 2 / 36), p.y + p.r * sin(i * M_PI * 2 / 36));
        glVertex2f(p.x + p.r * cos((i + 1) * M_PI * 2 / 36), p.y + p.r * sin((i + 1) * M_PI * 2 / 36));
    }
    glEnd();
}

float sqr(float x) {
    return x*x;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_POINTS);
    // for (int x = 0; x < 640; x += 2 * R) {
    //     for (int y = 0; y < 480; y += 2 * R) {
    //         glColor3f(0, 0, 0);
    //         glVertex2f(x, y);
    //     }
    // }
    // glEnd();

    for (int i = 0; i < N; i++) {
        glColor3f(0, 0, 0);
        drawParticle(p[i]);
    }
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        glColor3f(1, 0, 0);
        glVertex2f(path.v2[i].x, path.v2[i].y);
    }
    glEnd();
    glPointSize(1);

    glutSwapBuffers();
}
