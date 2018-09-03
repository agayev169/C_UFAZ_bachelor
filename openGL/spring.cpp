#include "GL/glut.h"
#include "GL/gl.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int DELTA_T = 10000; // mks

struct Particle {
    float x, y, vx, vy;
};

float sqr(float);

class Rubber {
public:
    vector<Particle> p;
    Rubber() {
        const int N = 10;//Particles
        for (int i = 0; i < N; i++) {
            Particle temp = { 320 + i * 200 / N, i * 20 / N, 0, 0};
            p.push_back(temp);
        }
    }
    void draw() const {
        glBegin(GL_LINE_STRIP);
        for(vector<Particle>::const_iterator i = p.begin(); i != p.end(); i++)
            glVertex2f(i->x, i->y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 36; i++) {
            glVertex2f(p.rbegin()->x + 10 * cos(2 * M_PI * i / 36), p.rbegin()->y + 10 * sin(2 * M_PI * i / 36));
            glVertex2f(p.rbegin()->x + 10 * cos(2 * M_PI * (i + 1) / 36), p.rbegin()->y + 10 * sin(2 * M_PI * (i + 1) / 36));
        }
        glEnd();
    }
    void tick() {
        for (int i = 1; i < p.size(); i++) {
            float ax = 0;
            float ay = 0;
            float a = 0;
            Particle &p0 = p[i-1];
            Particle &p1 = p[i];

            float d = sqrt(sqr(p1.x - p0.x) + sqr(p1.y - p0.y));
            const float rest = 180.0 / p.size();
            if(d > rest) a = 5.0 * (d - rest);
            // if(d < 2) a - 1E-4 * (2 - d);

            ax = a * (p0.x - p1.x) / d;
            ay = a * (p0.y - p1.y) / d;

            p1.vx += ax * DELTA_T / 1000000.0;
            p1.vy += ay * DELTA_T / 1000000.0;
            if (i != 1) {
                p0.vx -= ax * DELTA_T / 1000000.0;
                p0.vy -= ay * DELTA_T / 1000000.0;
            }
            Particle &p_ = *p.rbegin();
            p_.vy += 5.0 * DELTA_T / 1000000.0;
            for (vector<Particle>::iterator i = p.begin(); i != p.end(); i++) {
                i -> x += i -> vx * DELTA_T / 1000000.0;
                i -> y += i -> vy * DELTA_T / 1000000.0;
            }
        }
    }
};

Rubber r;

void display();
void timer(int);
void timer2(int = 0) {
    Particle &p = r.p[8];
    printf("%f\n", p.vx);
    glutTimerFunc(1000, timer2, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Pendulum");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 640.0, 480.0, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutTimerFunc(1, timer, 0);
    // glutTimerFunc(1000, timer2, 0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

float sqr(float x) {
    return x*x;
}

void timer(int) {
    for (int i = 0; i < 80000 / DELTA_T; i++) {
        r.tick();
    }
    display();
    glutTimerFunc(1, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    r.draw();
    glutSwapBuffers();
}
