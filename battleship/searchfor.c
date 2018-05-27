#include <stdio.h>
#include "battleship.h"
#include "searchfor.h"

void create_new_Cellarr(Cell cellarr[]){
   int row = 0, col = 0, index = 0;
   for(; row < SIZE; row++){
      col = 0;
      for(; col < SIZE; col++){
         cellarr[index++] = new_cell(row, col);
      }
   }
}

Cell new_cell(unsigned short row, unsigned short col){
   Cell c;
   c.row = row;
   c.col = col;
   c.state = OPEN_WATER;
   return c;
}

int insert_shot_res(Cell cellarr[], int shotres, Shot shot){
   int searchres = 0;
   if((searchres = search_for_cell(shot, cellarr)) >= 0){
      if(shotres == MISS)
         cellarr[searchres].state = shotres;
      else if(shotres == HIT){
         cellarr[searchres].state = HIT;
         return 1;
      }
      else if(shotres == SINK){
         cellarr[searchres].state = HIT;
         return 2;
      }
   }
   return -1;
}

int search_for_cell(Shot shot, Cell cellarr[]){
   if(shot.row >= SIZE || shot.col >= SIZE)
      return -1;
   return (10 * shot.row) + shot.col; 
}

void print_cell_dis(Cell cellarr[]){
   int i = 0;
   fprintf(stderr, "------ Current Cell dis -------\n");
   for(; i < SIZE * SIZE; i++){
      if ((i % 10) == 0){
         fprintf(stderr, "\n");
      }
      fprintf(stderr, "[%3d] ", cellarr[i].state);
   }
   fprintf(stderr, "\n\n --------------- end ----------------- \n\n");
}
