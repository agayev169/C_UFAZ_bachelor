#include <stdio.h>
#include <stdlib.h>
#include "Maze.h"

const int _x = 20, _y = 20;//number of pixels for each unit

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

//--------------------Maze-------------------------------------

Maze MZ_new (int width, int height) {
    Maze maze;
    maze.width = width;
    maze.height = height;
    maze.arr = (Cell*)calloc(width * height, sizeof(Cell));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze.arr[i*width+j] = CL_new(j, i);
            maze.arr[i*width+j].lc_number = 0;
            maze.arr[i*width+j] = CL_addLeftWall(maze.arr[i*width+j]);
            maze.arr[i*width+j] = CL_addRightWall(maze.arr[i*width+j]);
            maze.arr[i*width+j] = CL_addUpperWall(maze.arr[i*width+j]);
            maze.arr[i*width+j] = CL_addDownWall(maze.arr[i*width+j]);
            maze.arr[i*width+j].lc = (Cell*)calloc(4, sizeof(Cell));
        }
    }
    // maze.entrance.x = rand() % maze.width;
    // maze.entrance.y = rand() % maze.height;
    maze.entrance.x = 0;
    maze.entrance.y = 2;
    maze.entrance = maze.arr[maze.entrance.y * maze.width + maze.entrance.x];

    do {
        maze.exit.x = rand() % maze.width;
        maze.exit.y = rand() % maze.height;
    } while(CL_same(maze.entrance, maze.exit));
    maze.arr[maze.entrance.y * maze.width + maze.entrance.x] = CL_drawEntrance(maze.entrance);
    maze.arr[maze.exit.y * maze.width + maze.exit.x] = CL_drawExit(maze.exit);
    return maze;
}

void MZ_draw (Maze mz, FILE *f) {
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", _x*mz.width, _y*mz.height);
    fprintf(f, "255\n");
    for (int i = 0; i < mz.height; i++) {
        for (int k = 0; k < _y; k++) {
            for (int j = 0; j < mz.width; j++) {
                for (int l = 0; l < _x; l++) {
                    fprintf(f, "%d ", mz.arr[i*mz.width+j].color[k*_x+l]);
                }
                fprintf(f, "\n");
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n");
    }
}

Maze MZ_makePath (Maze mz, Cell cell, char been[]) {
    been[cell.y * mz.width + cell.x] = 1;
    cell = mz.arr[cell.y * mz.width + cell.x];
    if(cell.x != 0 && cell.x != mz.width - 1) {
        if(cell.y == 0) {
            char next;
            do {
                next = rand() % 4;
                if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                    cell = CL_deleteLeftWall(cell);
                    mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
                } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                    cell = CL_deleteRightWall(cell);
                    mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
                } else if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                    cell = CL_deleteDownWall(cell);
                    mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
                }
            } while (next == UP);
        } else if (cell.y == mz.height - 1) {
            char next;
            do {
                next = rand() % 4;
                if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                    cell = CL_deleteLeftWall(cell);
                    mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
                } else if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                    cell = CL_deleteUpperWall(cell);
                    mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
                } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                    cell = CL_deleteRightWall(cell);
                    mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
                }
            } while (next == DOWN);
        } else {
            char next = rand() % 4;
            // char next = DOWN;
            if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                cell = CL_deleteLeftWall(cell);
                mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
            } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                cell = CL_deleteRightWall(cell);
                mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
            } else if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                cell = CL_deleteUpperWall(cell);
                mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
            } else if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                cell = CL_deleteDownWall(cell);
                mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
            }
        }
    } else {
        if (cell.y != 0 && cell.y != mz.height) {
            if (cell.x == 0) {
                char next;
                do {
                    next = rand() % 4;
                    if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteDownWall(cell);
                        mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
                    } else if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteUpperWall(cell);
                        mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
                    } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                        cell = CL_deleteRightWall(cell);
                        mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
                    }
                } while (next == LEFT);
            } else if (cell.x == mz.width - 1) {
                char next;
                do {
                    next = rand() % 4;
                    if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteDownWall(cell);
                        mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
                    } else if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteUpperWall(cell);
                        mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
                    } else if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                        cell = CL_deleteLeftWall(cell);
                        mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
                    }
                } while (next == RIGHT);
            }
        } else if (cell.y == 0) {
            if (cell.x == 0) {
                char next;
                do {
                    next = rand() % 4;
                    if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteDownWall(cell);
                        mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
                    } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                        cell = CL_deleteRightWall(cell);
                        mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
                    }
                } while (next == LEFT || next == UP);
            } else if (cell.x == mz.width - 1) {
                char next;
                do {
                    next = rand() % 4;
                    if (next == DOWN && been[(cell.y + 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteDownWall(cell);
                        mz.arr[(cell.y + 1) * mz.width + cell.x] = CL_deleteUpperWall(mz.arr[(cell.y + 1) * mz.width + cell.x]);
                    } else if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                        cell = CL_deleteLeftWall(cell);
                        mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
                    }
                } while (next == RIGHT || next == UP);
            }
        } else if (cell.y == mz.height - 1) {
            if (cell.x == 0){
                char next;
                do {
                    next = rand() % 4;
                    if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteUpperWall(cell);
                        mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
                    } else if (next == RIGHT && been[cell.y * mz.width + cell.x + 1] == 0) {
                        cell = CL_deleteRightWall(cell);
                        mz.arr[cell.y * mz.width + cell.x + 1] = CL_deleteLeftWall(mz.arr[cell.y * mz.width + cell.x + 1]);
                    }
                } while (next == LEFT || next == DOWN);
            } else if (cell.x == mz.width - 1) {
                char next;
                do {
                    next = rand() % 4;
                    if (next == UP && been[(cell.y - 1) * mz.width + cell.x] == 0) {
                        cell = CL_deleteUpperWall(cell);
                        mz.arr[(cell.y - 1) * mz.width + cell.x] = CL_deleteDownWall(mz.arr[(cell.y - 1) * mz.width + cell.x]);
                    } else if (next == LEFT && been[cell.y * mz.width + cell.x - 1] == 0) {
                        cell = CL_deleteLeftWall(cell);
                        mz.arr[cell.y * mz.width + cell.x - 1] = CL_deleteRightWall(mz.arr[cell.y * mz.width + cell.x - 1]);
                    }
                } while (next == RIGHT || next == DOWN);
            }
        }
    }

    mz.arr[cell.y * mz.width + cell.x] = cell;
    return mz;
}

//--------------------Cell-------------------------------------

Cell CL_new (int x, int y) {
    Cell new;
    new.x = x;
    new.y = y;
    new.lc = (Cell*)calloc, sizeof(Cell);
    for (int i = 0; i < _x*_y; i++)
        new.color[i] = 255;
    return new;
}

void CL_draw (Cell cell, FILE *f) {
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", _x, _y);
    fprintf(f, "255\n");
    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++)
            fprintf(f, "%d ", cell.color[i*_x+j]);
        fprintf(f, "\n");
    }
}

Cell CL_drawEntrance (Cell cell) {
    for (int i = 0; i < _x*_y; i++)
        cell.color[i] = 150;
    cell = CL_addLeftWall(cell);
    cell = CL_addRightWall(cell);
    cell = CL_addUpperWall(cell);
    cell = CL_addDownWall(cell);
    return cell;
}

Cell CL_drawExit (Cell cell) {
    for (int i = 0; i < _x*_y; i++)
        cell.color[i] = 50;
    cell = CL_addLeftWall(cell);
    cell = CL_addRightWall(cell);
    cell = CL_addUpperWall(cell);
    cell = CL_addDownWall(cell);
    return cell;
}

Cell CL_addUpperWall (Cell cell) {
    for (int i = 0; i < _x/5; i++) {
        for (int j = 0; j < _y; j++) {
            cell.color[i*_x+j] = 0;
        }
    }
    return cell;
}

Cell CL_deleteUpperWall (Cell cell) {
    for (int i = 0; i < _x/5; i++) {
        for (int j = _y/5; j < _y*4/5; j++) {
            cell.color[i*_x+j] = 255;
            cell.lc[cell.lc_number] = CL_new(cell.x, cell.y + 1);
            cell.lc_number++;
        }
    }
    return cell;
}

Cell CL_addDownWall (Cell cell) {
    for (int i = _x*4/5; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            cell.color[i*_x+j] = 0;
        }
    }
    return cell;
}

Cell CL_deleteDownWall (Cell cell) {
    for (int i = _x*4/5; i < _x; i++) {
        for (int j = _y/5; j < _y*4/5; j++) {
            cell.color[i*_x+j] = 255;
            cell.lc[cell.lc_number] = CL_new(cell.x, cell.y - 1);
            cell.lc_number++;
        }
    }
    return cell;
}

Cell CL_addLeftWall (Cell cell) {
    for (int i = 0; i < _y; i++) {
        for (int j = 0; j < _x/5; j++) {
            cell.color[i*_x+j] = 0;
        }
    }
    return cell;
}

Cell CL_deleteLeftWall (Cell cell) {
    for (int i = _y/5; i < _y*4/5; i++) {
        for (int j = 0; j < _x/5; j++) {
            cell.color[i*_x+j] = 255;
            cell.lc[cell.lc_number] = CL_new(cell.x - 1, cell.y);
            cell.lc_number++;
        }
    }
    return cell;
}

Cell CL_addRightWall (Cell cell) {
    for (int i = 0; i < _y; i++) {
        for (int j = _y*4/5; j < _y; j++) {
            cell.color[i*_x+j] = 0;
        }
    }
    return cell;
}

Cell CL_deleteRightWall (Cell cell) {
    for (int i = _y/5; i < _y*4/5; i++) {
        for (int j = _x*4/5; j < _x; j++) {
            cell.color[i*_x+j] = 255;
            cell.lc[cell.lc_number] = CL_new(cell.x + 1, cell.y);
            cell.lc_number++;
        }
    }
    return cell;
}

char CL_same (Cell cell1, Cell cell2) {
    if(cell1.x == cell2.x && cell1.y == cell2.y) return TRUE;
    return FALSE;
}

//--------------------Stack-------------------------------------

Stack ST_new (int size) {
    Stack st;
    st.cells = (Cell*)calloc(size, sizeof(Cell));
    st.number_cells = 0;
    return st;
}
