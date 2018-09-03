#include "GL/glut.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

struct v2 {
    float x, y;
};

bool gameOver = false;

float const vx = -2;//Velocity of obstacles

float lastDestr = 0;//

int score = 0;

class Obstacle {
public:
    v2 obs[20];
    float height[10];
    int size;
    Obstacle() {
        for (int i = 0; i < 20; i++) {
            obs[i].x = 800;
            obs[i].y = 0;
        }
        size = 0;
    }

    void destroyObs() {
        // cout << "destroyed" << endl;
        // struct timeval tp;
        // gettimeofday(&tp, NULL);
        // if(lastDestr > tp.tv_sec * 1000 + tp.tv_usec / 1000) return;
        for (int i = 0; i < size - 2; i++) {
            obs[i].x = obs[i+2].x;
            obs[i].y = obs[i+2].y;
            height[i / 2] = height[(i+2) / 2];
        }
        score++;
        size -= 2;
        // lastDestr = tp.tv_sec * 1000 + tp.tv_usec / 1000 + 1000;
    }

    void newObs() {
        // cout << "new" << endl;
        srand(time(NULL));
        height[size/2] = 160 + rand() % 80 - 40;
        obs[size].x = 800; obs[size].y = 0;
        size++;
        obs[size].x = 800; obs[size].y = height[(size-1) / 2] + 40 +  260 - rand() % 80;
        size++;
    }

    void draw() {
        for (int i = 0; i < size; i += 2) {
            glColor3f(0, 1, 0);
            glBegin(GL_LINE_STRIP);
            glVertex2f(obs[i].x, obs[i].y);
            glVertex2f(obs[i].x, obs[i].y + height[i / 2]);
            glVertex2f(obs[i].x - 15, obs[i].y + height[i / 2]);
            glVertex2f(obs[i].x - 15, obs[i].y + height[i / 2] + 40);
            glVertex2f(obs[i].x + 115, obs[i].y + height[i / 2] + 40);
            glVertex2f(obs[i].x + 115, obs[i].y + height[i / 2]);
            glVertex2f(obs[i].x + 100, obs[i].y + height[i / 2]);
            glVertex2f(obs[i].x + 100, 0);
            glEnd();
        }

        for (int i = 1; i < size; i += 2) {
            glColor3f(0, 1, 0);
            glBegin(GL_LINE_STRIP);
            glVertex2f(obs[i].x, 480);
            glVertex2f(obs[i].x, obs[i].y);
            glVertex2f(obs[i].x - 15, obs[i].y);
            glVertex2f(obs[i].x - 15, obs[i].y - 40);
            glVertex2f(obs[i].x + 115, obs[i].y - 40);
            glVertex2f(obs[i].x + 115, obs[i].y);
            glVertex2f(obs[i].x + 100, obs[i].y);
            glVertex2f(obs[i].x + 100, 480);
            glEnd();
        }
    }
};

Obstacle obstacles;

class Bird {
public:
    float x, y;//positions
    float vy;//velocity components
    float r;//radius and mass
    Bird() {
        x = 200; y = 240; r = 30;
    }

    void draw() {
        glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 36; i++) {
            glVertex2f(x + r * cos((i) * M_PI / 18), y + r * sin((i) * M_PI / 18));
            glVertex2f(x + r * cos((i + 1) * M_PI / 18), y + r * sin((i + 1) * M_PI / 18));
        }
        glEnd();
    }

};

Bird bird;

void display();
void timer(int = 0);
void keyboard(unsigned char k, int x, int y);

int main(int argc, char *argv[]) {
    obstacles.newObs();//Creating new obstacles
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flappy Bird");
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glClearColor(128.0/255, 166.0/255, 255.0/255, 1);
    glutKeyboardFunc(keyboard);
    timer();
    glutMainLoop();

    return 0;
}

void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case ' ':
        case 'w':
            bird.vy -= 10;
            break;
    }
}

void timer(int) {
    display();

    //Game Over
    if (bird.y > 540 || bird.y < -60) gameOver = true;
    for (int i = 1; i < obstacles.size; i += 2) {
        if ((bird.x > obstacles.obs[i].x - 15 && bird.x < obstacles.obs[i].x + 15 + 100 &&
            bird.y < obstacles.height[i / 2] + 40 && bird.y > 0) ||
            (bird.x > obstacles.obs[i].x - 15 && bird.x < obstacles.obs[i].x + 15 + 100 &&
            bird.y > obstacles.obs[i].y - 40 && bird.y < 480)) {
             gameOver = true;

         }
    }

    if (gameOver){
        for (int i = 0; i < obstacles.size; i += 2) {
            if (bird.x > obstacles.obs[i].x + 100 + bird.r)
                score++;
        }
        cout << "Game Over! Score: " << score << endl; exit(0);
    }
    //Motion of bird
    bird.vy += 0.001 * bird.r * 9.81;
    bird.y += bird.vy;
    //Adding obstacles
    if (obstacles.obs[0].x <= -150) {
        obstacles.destroyObs();
        // obstacles.newObs();
    }
    if (obstacles.obs[obstacles.size-1].x <= 500) obstacles.newObs();
    //Moving obstacles
    for (int i = 0; i < obstacles.size; i++)
        obstacles.obs[i].x += vx;

    glutTimerFunc(10, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    bird.draw();
    obstacles.draw();

    glutSwapBuffers();
}
