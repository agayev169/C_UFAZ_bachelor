#include <stdio.h>

struct Cell
{
    int x;
    int y;
};

typedef struct Cell Cell;

Cell newCell(int x, int y){
    Cell a;
    a.x=x;
    a.y=y;
    return a;
}

void printCell(Cell a){
    printf("The x component of cell: %d and y component: %d \n",a.x,a.y );
}

int compareCell(Cell a, Cell b){
    if ((a.x==b.x) && (a.y==b.y))
        return 1;
    else
        return 0;
}

int compareCellviaInt(int ax, int ay, Cell b){
    if ((ax==b.x) && (ay==b.y))
        return 1;
    else
        return 0;
}

Cell CL_entrance(Maze mz){
    Cell a;
    MZ_entrance(mz, &a.x, &a.y);
    return a;
}

Cell CL_exit(Maze mz){
    Cell a;
    MZ_exit(mz, &a.x, &a.y);
    return a;
}

int CL_linkedCells(Maze mz, Cell a , Cell *array){
    int tmp[8];
    int nb_links=MZ_linkedCells(mz, a.x, a.y, tmp);
    for (int i = 0; i < 2*nb_links; i+=2)
    {
        array[i/2].x=tmp[i];
        array[i/2].y=tmp[i+1];
    }
    return nb_links;
}

void CL_solution(Maze mz, int solution_cells[], int nb_cells ){
    MZ_setSolution(mz, solution_cells, nb_cells);
    MZ_saveImg(mz,"solution.ppm");
}

int neighbourEntranceExitEasy(Maze mz, Cell mid, Cell ent, Cell ext, Cell *linked_cells){
    int nb_links = CL_linkedCells(mz, mid, linked_cells);
    int neighbourwithEntrance=0;
    int neighbourwithExit=0;
    for (int k = 0; k < nb_links; k++)
    {
        if(compareCell(linked_cells[k],ext))
            neighbourwithExit=1;
        else if(compareCell(linked_cells[k],ent))
            neighbourwithEntrance=1;
    }
    if(neighbourwithEntrance==1 && neighbourwithExit==1)
        return 1;
    else
        return 0;
}

int CellCheckEasy(Maze mz){
    Cell entrance=CL_entrance(mz);
    Cell exit=CL_exit(mz);
    Cell mid;
    Cell path[3];
    path[0]=entrance;
    path[2]=exit;
    int width,height;
    Cell linked_cells[4];
    MZ_size(mz, &width, &height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            mid.x=i;
            mid.y=j;
            if(neighbourEntranceExitEasy(mz, mid, entrance, exit, linked_cells))
            {
                path[1]=mid;
                int solution_cells[6];
                for (int z = 0; z < 6; z+=2)
                {
                    solution_cells[z]=path[z/2].x;
                    solution_cells[z+1]=path[z/2].y;
                }
                CL_solution(mz, solution_cells, 3);
                return 1;
            }
        }
    }
    return 0;
}


void unExploredLinkedCell(Maze mz, Cell entrance, Cell exit , int *shet, int *path){
    int linked_cells[4];
    int ax;//eto prediduwiy x
    int bx;//eto sled x
    int ay;//eto prediduwiy y
    int by;//eto sled y
    Cell solution[64];
    int counter=1;
    int n=0;
    int nb_links=MZ_linkedCells(mz, entrance.x+1, entrance.y+1, linked_cells);
    for (int i = 0; i < 64; i++)
    {
        if (i==0)
        {
            solution[i].x=entrance.x;
            solution[i].y=entrance.y;
        }
        ax=linked_cells[0];
        ay=linked_cells[1];
        bx=linked_cells[2];
        by=linked_cells[3];
        counter++;
        if (compareCellviaInt(ax,ay,solution[i]))
        {
            solution[i+1].x=bx;
            solution[i+1].y=by;
        }else{
            solution[i+1].x=ax;
            solution[i+1].y=ay;
        }
         if (compareCell(solution[i+1],exit)){
             int path[counter*2];
             for (int i = 0; i < counter; i+2)
             {
                 n=i+1;
                 path[i]=solution[i].x;
                 path[n]=solution[i].y;
             }
             *shet=counter*2;
             break;
        }
        nb_links=MZ_linkedCells(mz, solution[i+1].x, solution[i+1].y, linked_cells);
    }
}

// int unExploredLinkedCell(Maze mz, Cell entrance, Cell exit , int *shet){
//     int linked_cells[8];
//     // Cell a;//eto prediduwiy
//     // Cell b;//eto sled
//     int ax;//eto prediduwiy x
//     int bx;//eto sled x
//     int ay;//eto prediduwiy y
//     int by;//eto sled y
//     int solution[128];
//     int holdCounter;
//     int counter=1;
//     int n=0;
//     Cell position;
//     static int solutionPosition=0;
//     int nb_links=MZ_linkedCells(mz, entrance.x,entrance.y, linked_cells);
//     // while(compareCell(position,exit)){
//         switch(nb_links) {
//             case 1:
//                 if (compareCell(position,exit))
//                 {
//                     solution[solutionPosition]=position.x;
//                     solutionPosition+=1;
//                     solution[solutionPosition]=position.y;
//                     solutionPosition+=1;
//                     *shet=counter;
//                     return solution;
//                 }
//                 // else
//                 //     return 0;
//                 break;
//             case 2:
//             ax = linked_cells[0];
//             ay = linked_cells[1];
//             bx = linked_cells[2];
//             by = linked_cells[3];
//             if (compareCellviaInt(ax, ay, position))
//             {
//                 solution[solutionPosition]=bx;
//                 solutionPosition+=1
//                 solution[solutionPosition]=by;
//                 solutionPosition+=1;
//                 if (compareCellviaInt(bx , by, exit))
//                 {
//                     *shet=counter;
//                     return solution;
//                 }
//             }else{
//                 solution[solutionPosition]=ax;
//                 solutionPosition+=1
//                 solution[solutionPosition]=ay;
//                 solutionPosition+=1;
//                 if (compareCellviaInt(ax , ay, exit))
//                 {
//                     *shet=counter;
//                     return solution;
//                 }
//             }

//         }
//     // }

// }

// void findOneway(Maze mz,Cell exit,Cell position,int solution[],int* nb_cells){
//     int linked_cells[4];
//     int nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
//     int width,height;
//     MZ_size(mz, &width, &height);
//     int path[width*height];
//     int i=0;
//     int ff=1;
//     while(ff){
//         if (compareCellviaInt(linked_cells[0],linked_cells[1],position))
//         {
//             if (compareCellviaInt(linked_cells[2],linked_cells[3],exit))
//             {
//                 path[i]=linked_cells[2];
//                 path[i+1]=linked_cells[3];
//                 i+=2;
//                 for (int x = 0; x < i;x++)
//                 {
//                     solution[x]=path[x];
//                 }
//                 *nb_cells=i;
//                 ff=0;
//             }else{
//                 path[i]=linked_cells[2];
//                 path[i+1]=linked_cells[3];
//                 i+=2;
//                 position.x=linked_cells[2];
//                 position.y=linked_cells[3];
//                 nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
//             }
//         }else{
//             if (compareCellviaInt(linked_cells[0],linked_cells[1],exit))
//             {
//                 path[i]=linked_cells[0];
//                 path[i+1]=linked_cells[1];
//                 i+=2;
//                 for (int x = 0; x < i;x++)
//                 {
//                     solution[x]=path[x];
//                 }
//                 *nb_cells=i;
//                 ff=0;
//             }else{
//                 path[i]=linked_cells[0];
//                 path[i+1]=linked_cells[1];
//                 i+=2;
//                 position.x=linked_cells[0];
//                 position.y=linked_cells[1];
//                 nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
//             }
//         }
//     }
// }