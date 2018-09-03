#include "GL/glut.h"
#include <math.h>

const float K = 40;
const float DT = 0.03;

struct P {
    P(): z(0), vz(0) {}
    float x, y, z, vz;
};

int const N = 80;

P p[N][N];


void display();
void timer(int = 0);
void keyboard(unsigned char k, int x, int y);

int main(int argc, char *argv[]) {

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            p[x][y].x = x * 800 / N;
            p[x][y].y = y * 800 / N;
        }

    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-100, 100, -100, 100, 100, 2000);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-400, -400, -600);
    glRotatef(-30, 1, 0, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    timer();
    glutMainLoop();

    return 0;
}

void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case ' ':
        p[rand() % (N - 2) + 1][rand() % (N-2) + 1].vz += 300;
        break;
    }
}

void timer(int) {
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};

    // if(rand() % 50 == 0)
    //     p[rand() % (N - 2) + 1][rand() % (N-2) + 1].vz += 300;

    for (int x = 1; x < N - 1; x++) {
        for (int y = 1; y < N - 1; y++) {
            P &p0 = p[x][y];
            for (int i = 0; i < 4; i++) {
                P &p1 = p[x + dx[i]][y + dy[i]];
                const float d = sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
                p0.vz += K * (p1.z - p0.z) / d * DT;
                p0.vz *= 0.999;
            }
        }
    }
        for (int x = 1; x < N - 1; x++) {
            for (int y = 1; y < N - 1; y++) {
                P &p0 = p[x][y];
                p0.z += p0.vz;
            }
        }
    display();
    glutTimerFunc(1, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    for (int x = 0; x < N; x++) {
        glBegin(GL_LINE_STRIP);
        for (int y = 0; y < N; y++) {
            glVertex3f(p[x][y].x, p[x][y].y, p[x][y].z);
        }
        glEnd();
    }

    for (int y = 0; y < N; y++) {
        glBegin(GL_LINE_STRIP);
        for (int x = 0; x < N; x++) {
            glVertex3f(p[x][y].x, p[x][y].y, p[x][y].z);
        }
        glEnd();
    }
    glutSwapBuffers();
}
