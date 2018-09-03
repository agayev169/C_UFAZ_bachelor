#include <stdio.h>
#include "Maze.h"
#include "Cell.h"

void findOneway(Maze mz,Cell exit,Cell entrance,int solution[],int* nb_cells ){
    int linked_cells[4];
    int nb_links=MZ_linkedCells(mz, entrance.x, entrance.y, linked_cells);
    int width,height;
    for (int k = 0; k < nb_links*2;k++)
    {
        printf("This is first link %d\n",linked_cells[k] );
    }
    MZ_size(mz, &width, &height);
    int path[64];
    Cell preposition=entrance;
    Cell position;
    int i=0;
    int ff=1;
    printf("position x : %d  y : %d \n",position.x,position.y );
    path[i]=entrance.x;
    printf("Path [0] : %d \n" , path[i]);
    path[i+1]=entrance.y;
    printf("Path [1] : %d \n" , path[i+1]);
    i+=2;
        if (compareCellviaInt(linked_cells[0],linked_cells[1],exit))
            {
                printf("Value of i %d\n",i );
                path[i]=linked_cells[0];
                printf("Value of i %d\n",i );
                path[i+1]=linked_cells[1];
                i+=2;
                printf("Value of i %d\n\n",i );
                printf("position x : %d  y : %d \n",position.x,position.y );
                for (int x = 0; x < i;x++  )
                {
                    solution[x]=path[x];
                    // *point_to_start++;
                }
                printf("solution[0]: %d solution[1]: %d \n" , solution[0],solution[1] );
                printf("path[0]: %d path[1]: %d \n" , path[0],path[1] );
                *nb_cells=i/2;
                ff=0;
            }else{
                path[i]=linked_cells[0];
                printf("Value of i %d\n",i );
                printf("Path [2] : %d \n" , path[i]);
                path[i+1]=linked_cells[1];
                printf("Path [3] : %d \n" , path[i+1]);
                printf("Value of i %d\n",i );
        printf("---------------------\n");
        printf("path [0] = %d %d\n", path[0], path[1]);
                i+=2;
                printf("Value of i %d\n\n",i );
                printf("position x : %d  y : %d \n",position.x,position.y );
                position.x=linked_cells[0];
                position.y=linked_cells[1];
        printf("---------------------\n");
        printf("path [0] before nb_links = %d %d\n", path[0], path[1]);
                nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
        printf("---------------------\n");
        printf("path [0] after nb_links = %d %d\n", path[0], path[1]);
                for (int k = 0; k < nb_links*2;k++)
                {
                    printf("This is first link %d\n",linked_cells[k] );
                }
            }

    while(ff){
        printf("---------------------\n");
        printf("path [0] = %d %d\n", path[0], path[1]);
        if (compareCellviaInt(linked_cells[0],linked_cells[1],preposition))
        {
            if (compareCellviaInt(linked_cells[2],linked_cells[3],exit)){
                printf("Value of i %d\n",i );
                path[i]=linked_cells[2];
                printf("Value of i %d\n",i );
                path[i+1]=linked_cells[3];
                printf("Value of i %d\n\n",i );
                printf("position x : %d  y : %d \n",position.x,position.y );
                printf("Hello 103\n");
                i+=2;
                printf("Value of i %d\n",i );
                for (int x = 0; x < i;x++  )
                {
                    solution[x]=path[x];
                    // *point_to_start++;
                    printf("Hello 109\n");
                }
                printf("solution[0]: %d solution[1]: %d \n" , solution[0],solution[1] );
                printf("path[0]: %d path[1]: %d \n" , path[0],path[1] );
                *nb_cells=i/2;
                ff=0;
            }else{
                printf("Value of i %d\n",i );
                path[i]=linked_cells[2];
                printf("Value of i %d\n",i );
                path[i+1]=linked_cells[3];
                printf("Value of i %d\n",i );
                printf("Hello 115\n");
                i+=2;
                printf("Value of i %d\n\n",i );
                printf("position x : %d  y : %d \n",position.x,position.y );
                preposition=position;
                position.x=linked_cells[2];
                position.y=linked_cells[3];
                nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
                for (int k = 0; k < nb_links*2;k++)
                {
                    printf("This is first link %d\n",linked_cells[k] );
                }
            }
        }else{
        
            if (compareCellviaInt(linked_cells[0],linked_cells[1],exit)){
                    printf("Value of i %d\n",i );
                    path[i]=linked_cells[0];
                    printf("Value of i %d\n",i );
                    path[i+1]=linked_cells[1];
                    printf("Hello 127\n");
                    i+=2;
                    printf("Value of i %d\n\n",i );
                    printf("position x : %d  y : %d \n",position.x,position.y );
                    for (int x = 0; x < i;x ++  )
                    {
                        solution[x]=path[x];
                        // *point_to_start++;
                        // printf("Hello 133\n");
                    }
                    printf("solution[0]: %d solution[1]: %d \n" , solution[0],solution[1] );
                    printf("path[0]: %d path[1]: %d \n" , path[0],path[1] );
                    *nb_cells=i/2;
                    ff=0;
            }else{
                    printf("Value of i %d\n",i );
                    path[i]=linked_cells[0];
                    printf("Value of i %d\n",i );
                    path[i+1]=linked_cells[1];
                    printf("Hello 139\n");
                    i+=2;
                    printf("Value of i %d\n\n",i );
                    printf("position x : %d  y : %d \n",position.x,position.y );
                    preposition=position;
                    position.x=linked_cells[0];
                    position.y=linked_cells[1];
                    printf("Hello 143\n");
                    nb_links=MZ_linkedCells(mz, position.x, position.y, linked_cells);
                    for (int k = 0; k < nb_links*2;k++)
                    {
                        printf("This is first link %d\n",linked_cells[k] );
                    }
            }
        }
    }    
}




int main()
{
    Maze mz = MZ_new(8,8,MZ_MEDIUM);
    int width,height;
    MZ_size(mz, &width, &height);
    int solution[64];
    int nb_cells=0;
    Cell entrance=CL_entrance(mz);
    Cell exit = CL_exit(mz);
    // int point_to_start=0;
    findOneway(mz, exit, entrance, solution,&nb_cells);
    int final_solution[nb_cells];
    for (int k = 0; k < nb_cells*2; k+=2)
    {
        printf("x: %d  y: %d \n",solution[k],solution[k+1] );
        // final_solution[k]=solution[k];
    }
    // Cell entrance=CL_entrance(mz);
    // Cell exit=CL_exit(mz);
    // int counter=0;
    // int solution[64];
    // unExploredLinkedCell( mz,  entrance,  exit , &counter, solution);
    // int n=0;
    // for (int i = 0; i < counter; i+2)
    // {
    //     n=i+1;
    //     printf("The path is (%d,%d)\n",solution[i],solution[n] );
    // }
    MZ_setSolution(mz, solution, 22);
    
    MZ_saveImg(mz,"asd.ppm");
    // CellCheckEasy( mz);
    // MZ_saveImg(mz, "123.ppm");
    MZ_free(mz);
    return 0;
}