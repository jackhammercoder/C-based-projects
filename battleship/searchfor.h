#ifndef SEARCHFOR_H
#define SEARCHFOR_H

#include "battleship.h"

typedef struct{
   int row;
   int col;
   int state;
} Cell;

/* this function intializes an array of Cell structures
* they will have a initial value of 1 since they are equally ditributed
*/

void create_new_Cellarr(Cell cellarr[]);

/* this function is a helper function that creates a new_cell
* it will have a intial value of OPEN_WATER for each cell
* later to be changed MISS, HIT, or SINK
*/

Cell new_cell(unsigned short row, unsigned short col);

/* This function takes a shot and a shot result from the host
* and then in inserts the result of the shot into the cell ARRAY
* if it couldn't find the shot then it must mean that the shot the 
* opponenet set is garbage. Thus we must not store it in our shout sequence
* array. 
*/

int insert_shot_res(Cell cellarr[], int shotres, Shot shot);

/* This is a helper funtion for insert_shot_res.
* it will look for the particular row and column combo
* in the cell array. If it finds it will return the index of
* that shot if not it will return -1
*/

int search_for_cell(Shot shot, Cell cellarr[]);

/* this function is for teting purposes it will just 
* print the current states of each cell in the board
*/

void print_cell_dis(Cell cellarr[]);

#endif