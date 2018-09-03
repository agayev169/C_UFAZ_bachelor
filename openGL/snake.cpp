#include "GL/glut.h"
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

using namespace std;

int const dx = 15;
int const dy = 15;

int const max_size = 100;

struct v2 {
    float x, y;// between width(height) of screen / dx(dy)
};

class Snake {
public:
    int dest, size;
    float k;
    v2 sn[max_size];
    Snake(float x, float y) {
        dest = RIGHT;
        for (int i = 0; i < max_size; i++)
            sn[i].x = sn[i].y = -20;
        for (int i = 0; i < 4; i++) {
            sn[i].x = x + i;
            sn[i].y = y;
            size = 4;
        }
    }
};

Snake snake(5, 5);

class Food {
public:
    v2 pos;
    Food() {
        srand(time(NULL));
        pos.x = rand() % (640 / dx);
        pos.y = rand() % (480 / dy);
    }
    void eat() {
        pos.x = rand() % (640 / dx);
        pos.y = rand() % (480 / dy);
        for (int i = 0; i < snake.size; i++) {
            if (snake.sn[i].x == pos.x && snake.sn[i].y == pos.y) {
                eat();
            }
        }
    }
};

Food food;

class Poison {
public:
    v2 pos[max_size];
    int size;
    Poison() {
        for (int i = 0; i < max_size; i++) {
            pos[i].x = -20;
            pos[i].y = -20;
        }
        pos[0].x = rand() % (640 / dx);
        pos[0].y = rand() % (480 / dy);
        size = 1;
    }
    void newP() {
        pos[size].x = rand() % (640 / dx);
        pos[size].y = rand() % (480 / dy);
        for (int i = 0; i < snake.size; i++) {
            if ((snake.sn[i].x == pos[size].x && snake.sn[i].y == pos[size].y) || (food.pos.x == pos[size].x && food.pos.y == pos[size].y)) {
                newP();
            }
        }
        size++;
    }
};

Poison poison;

void display();
void timer(int = 0);
void keyboard(unsigned char k, int x, int y);
void keyboardSpecial(int k, int x, int y);

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Classic Snake");
    glutInitDisplayMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, -1, 1);
    glutInitDisplayMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    timer();
    glutMainLoop();

    return 0;
}

long int last = 0;//Last time there was a button pushed

void keyboard(unsigned char k, int x, int y){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    if(last > tp.tv_sec * 1000 + tp.tv_usec / 1000) return;
    switch (k) {
        case 'w':
            if (snake.dest == UP || snake.dest == DOWN) break;
            else snake.dest = UP;
            break;
        case 'd':
            if (snake.dest == LEFT || snake.dest == RIGHT) break;
            else snake.dest = RIGHT;
            break;
        case 's':
            if (snake.dest == UP || snake.dest == DOWN) break;
            else snake.dest = DOWN;
            break;
        case 'a':
            if (snake.dest == LEFT || snake.dest == RIGHT) break;
            else snake.dest = LEFT;
            break;
    }
    last = tp.tv_sec * 1000 + tp.tv_usec / 1000 + 200;

}

void keyboardSpecial(int k, int x, int y) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    if(last > tp.tv_sec * 1000 + tp.tv_usec / 1000) return;
    switch (k) {
        case GLUT_KEY_UP:
            if (snake.dest == UP || snake.dest == DOWN) break;
            else snake.dest = UP;
            break;
        case GLUT_KEY_RIGHT:
            if (snake.dest == LEFT || snake.dest == RIGHT) break;
            else snake.dest = RIGHT;
            break;
        case GLUT_KEY_DOWN:
            if (snake.dest == UP || snake.dest == DOWN) break;
            else snake.dest = DOWN;
            break;
        case GLUT_KEY_LEFT:
            if (snake.dest == LEFT || snake.dest == RIGHT) break;
            else snake.dest = LEFT;
            break;
    }
    last = tp.tv_sec * 1000 + tp.tv_usec / 1000 + 200;
}

void timer(int) {
    //Eating, growing and adding a new poison
    if(snake.sn[snake.size - 1].x == food.pos.x && snake.sn[snake.size - 1].y == food.pos.y) {
        food.eat();
        if (snake.size < max_size) {
            snake.sn[snake.size].x = snake.sn[snake.size - 1].x;
            snake.sn[snake.size].y = snake.sn[snake.size - 1].y;
            snake.size++;
            poison.newP();
        }
    }

    //Motion
    for (int i = 1; i < snake.size; i++) {
        snake.sn[i - 1].x = snake.sn[i].x;
        snake.sn[i - 1].y = snake.sn[i].y;
    }
    if (snake.dest == RIGHT) {
        snake.sn[snake.size - 1].x++;
    }
    if (snake.dest == UP) {
        snake.sn[snake.size - 1].y--;
    }
    if (snake.dest == LEFT) {
        snake.sn[snake.size - 1].x--;
    }
    if (snake.dest == DOWN) {
        snake.sn[snake.size - 1].y++;
    }

    //Walls
    if(snake.sn[snake.size - 1].x <= 0) snake.sn[snake.size - 1].x += 640 / dx;
    if(snake.sn[snake.size - 1].x >= 640 / dx) snake.sn[snake.size - 1].x -= 640 / dx;
    if(snake.sn[snake.size - 1].y <= 0) snake.sn[snake.size - 1].y += 480 / dy;
    if(snake.sn[snake.size - 1].y >= 480 / dy) snake.sn[snake.size - 1].y -= 480 / dy;

    //Game Over
    for (int i = 0; i < snake.size - 1; i++) {
        if(snake.sn[snake.size - 1].x == snake.sn[i].x && snake.sn[snake.size - 1].y == snake.sn[i].y) {cout << "Game Over!" << endl;exit(0);}
    }

    for (int i = 0; i < poison.size; i++) {
        if (snake.sn[snake.size - 1].x == poison.pos[i].x && snake.sn[snake.size - 1].y == poison.pos[i].y) {cout << "Game Over!" << endl;exit(0);}
    }

    display();
    glutTimerFunc(200 - snake.size, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    //Grid
    glBegin(GL_POINTS);
    for (int x = 0; x < 640; x += dx) {
        for (int y = 0; y < 480; y += dy) {
            glVertex2f(x, y);
        }
    }
    glEnd();

    //Snake
    glColor3f(0, 0, 0);
    for (int i = 0; i < snake.size; i++) {
        v2 &p = snake.sn[i];
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < 36; j++) {
            glVertex2f((p.x + cos(j * M_PI / 18)/2) * dx + dx/2, (p.y + sin(j * M_PI / 18)/2) * dx + dy/2);
            glVertex2f((p.x + cos((j + 1) * M_PI / 18)/2) * dx + dx/2, (p.y + sin((j + 1) * M_PI / 18)/2) * dx + dy/2);
        }
        glEnd();
    }

    //Food
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 36; i++) {
        for (float dr = 0; dr < dx; dr += .09) {
            glVertex2f((food.pos.x * dx + cos(i * M_PI / 18)/2 * dr) + dx/2, (food.pos.y * dx + sin(i * M_PI / 18)/2 * dr) + dy/2);
            glVertex2f((food.pos.x * dy + cos((i + 1) * M_PI / 18)/2 * dr) + dx/2, (food.pos.y * dy + sin((i + 1) * M_PI / 18)/2 * dr) + dy/2);
        }
    }
    glEnd();

    //Poisons
    glColor3f(1, 0, 0);
    for (int j = 0; j < poison.size; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 36; i++) {
            for (float dr = 0; dr < dx; dr += .09) {
                glVertex2f((poison.pos[j].x * dx + dr * cos(i * M_PI / 18)/2) + dx/2, (poison.pos[j].y * dy + dr * sin(i * M_PI / 18)/2) + dy/2);
                glVertex2f((poison.pos[j].x * dx + dr * cos((i + 1) * M_PI / 18)/2) + dx/2, (poison.pos[j].y * dy + dr * sin((i + 1) * M_PI / 18)/2) + dy/2);
            }
        }
        glEnd();
    }

    glutSwapBuffers();
}
