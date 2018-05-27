#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "battleship.h"
#include "PDFshot.h"
#include "searchfor.h"
#include "updatePDF.h"
 
static int getFD(const char *arg)
{
   int fd;

   if (1 != sscanf(arg, "%d", &fd))
   {
      fprintf(stderr, "Bad fd argument\n");
      exit(EXIT_FAILURE);
   }

   return fd;
}

static void defBoard1(char board[][SIZE]){
   int i =0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         board[i][j] = OPEN_WATER;
      }
   }
   board[5][9] = AIRCRAFT_CARRIER;
   board[6][9] = AIRCRAFT_CARRIER;
   board[7][9] = AIRCRAFT_CARRIER;
   board[8][9] = AIRCRAFT_CARRIER;
   board[9][9] = AIRCRAFT_CARRIER;
   
   board[9][4] = BATTLESHIP;
   board[9][5] = BATTLESHIP;
   board[9][6] = BATTLESHIP;
   board[9][7] = BATTLESHIP;

   board[9][1] = DESTROYER;
   board[9][2] = DESTROYER;
   board[9][3] = DESTROYER;

   board[0][0] = SUBMARINE;
   board[0][1] = SUBMARINE;
   board[0][2] = SUBMARINE;

   board[4][0] = PATROL_BOAT;
   board[5][0] = PATROL_BOAT;
}

static void defBoard2(char board[][SIZE]){
   int i =0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         board[i][j] = OPEN_WATER;
      }
   }
   board[0][5] = AIRCRAFT_CARRIER;
   board[0][6] = AIRCRAFT_CARRIER;
   board[0][7] = AIRCRAFT_CARRIER;
   board[0][8] = AIRCRAFT_CARRIER;
   board[0][9] = AIRCRAFT_CARRIER;
   
   board[9][0] = BATTLESHIP;
   board[9][1] = BATTLESHIP;
   board[9][2] = BATTLESHIP;
   board[9][3] = BATTLESHIP;

   board[4][4] = DESTROYER;
   board[4][5] = DESTROYER;
   board[4][6] = DESTROYER;

   board[7][9] = SUBMARINE;
   board[8][9] = SUBMARINE;
   board[9][9] = SUBMARINE;

   board[0][0] = PATROL_BOAT;
   board[1][0] = PATROL_BOAT;
}

static void defBoard3(char board[][SIZE]){
   int i =0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         board[i][j] = OPEN_WATER;
      }
   }
   board[1][3] = AIRCRAFT_CARRIER;
   board[1][4] = AIRCRAFT_CARRIER;
   board[1][5] = AIRCRAFT_CARRIER;
   board[1][6] = AIRCRAFT_CARRIER;
   board[1][7] = AIRCRAFT_CARRIER;
   
   board[3][4] = BATTLESHIP;
   board[3][3] = BATTLESHIP;
   board[3][2] = BATTLESHIP;
   board[3][1] = BATTLESHIP;

   board[4][6] = DESTROYER;
   board[4][7] = DESTROYER;
   board[4][8] = DESTROYER;

   board[6][1] = SUBMARINE;
   board[6][2] = SUBMARINE;
   board[6][3] = SUBMARINE;

   board[8][7] = PATROL_BOAT;
   board[8][8] = PATROL_BOAT;
}

static void defBoard4(char board[][SIZE]){
   int i =0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         board[i][j] = OPEN_WATER;
      }
   }
   board[1][0] = AIRCRAFT_CARRIER;
   board[1][1] = AIRCRAFT_CARRIER;
   board[1][2] = AIRCRAFT_CARRIER;
   board[1][3] = AIRCRAFT_CARRIER;
   board[1][4] = AIRCRAFT_CARRIER;
   
   board[5][8] = BATTLESHIP;
   board[6][8] = BATTLESHIP;
   board[7][8] = BATTLESHIP;
   board[8][8] = BATTLESHIP;

   board[9][0] = DESTROYER;
   board[9][1] = DESTROYER;
   board[9][2] = DESTROYER;

   board[0][8] = SUBMARINE;
   board[1][8] = SUBMARINE;
   board[2][8] = SUBMARINE;

   board[2][4] = PATROL_BOAT;
   board[2][5] = PATROL_BOAT;
}

static void defBoard5(char board[][SIZE]){
   int i =0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         board[i][j] = OPEN_WATER;
      }
   }
   board[1][8] = AIRCRAFT_CARRIER;
   board[2][8] = AIRCRAFT_CARRIER;
   board[3][8] = AIRCRAFT_CARRIER;
   board[4][8] = AIRCRAFT_CARRIER;
   board[5][8] = AIRCRAFT_CARRIER;
   
   board[2][1] = BATTLESHIP;
   board[2][2] = BATTLESHIP;
   board[2][3] = BATTLESHIP;
   board[2][4] = BATTLESHIP;

   board[4][4] = DESTROYER;
   board[5][4] = DESTROYER;
   board[6][4] = DESTROYER;

   board[6][2] = SUBMARINE;
   board[7][2] = SUBMARINE;
   board[8][2] = SUBMARINE;

   board[7][6] = PATROL_BOAT;
   board[7][7] = PATROL_BOAT;
}

static void writeboard(int fd, char board[][SIZE], unsigned short *k, 
   unsigned short *l, unsigned short game_no){
   int i = 0, j = 0;
   *k = 0;
   *l = 0;
   
   if(game_no == 1)
      defBoard1(board); 
   
   else if(game_no == 2)
      defBoard2(board);

   else if(game_no == 3){
      defBoard3(board);
   }
   else if(game_no == 4)
      defBoard4(board);
   else
      defBoard5(board);

   for(; i < SIZE ; i++){
      j = 0;
      for(; j < SIZE; j++){
         write(fd, &(board[i][j]),sizeof(char));
      }
   }
}

static void sendshot(Shot* sh, int fd){
   write(fd, sh, sizeof(Shot));
}

void init_hit(int hitarr[]){
   int i = 0;
   for(; i < SIZE * SIZE; i++){
      hitarr[i] = -1;
   }
}

int sort_hits(const void* ind1, const void* ind2){
   int *curr, *next;

   curr = (int*) ind1;
   next = (int*) ind2;

   if(*curr == *next){
      return 0;
   }
   else if(*curr < *next){
      return 1;
   }
   return -1;
}

int compare_hits(int prev_hits[], int curr_hits[], int prev_len, int curr_len){
   int smallerarr = 0, alike = 0, i = 0;
   if(prev_len < curr_len)
      smallerarr = prev_len;
   else{
      smallerarr = curr_len;
   }
   qsort(prev_hits, SIZE * SIZE, sizeof(int), sort_hits);
   qsort(curr_hits, SIZE * SIZE, sizeof(int), sort_hits);
   
   for(; i < smallerarr; i++){
      if(prev_hits[i] == curr_hits[i])
         alike++;
      else
         break;
   }
   if(alike == 0){
      return -1;
   }
   return 1;
}

void logic(int readFD, int writeFD, char board[][SIZE], int signal){
   unsigned short i = 0, j = 0;
   unsigned game_number = 0;
   int res = 0, same_ship_strat = 0,
      curr_hit_in = 0, prev_hit_in = 0, ind = 0;
   int prev_hits[SIZE * SIZE], curr_hits[SIZE * SIZE];  
   PDFshot my_shots[SIZE * SIZE];
   PDFshot buffer[SIZE * SIZE];
   Cell cell_arr[SIZE * SIZE];
   Hunt find;
   Shot currshot, opp_shot;
   find = new_hunt();
   init_hit(curr_hits);
   init_hit(prev_hits);
   while(1)
   {
      read(readFD,&signal,sizeof(int));
      
      if (signal == NEW_GAME){
         game_number++;
         same_ship_strat = -1;
         create_new_Cellarr(cell_arr);
         create_new_pdf(my_shots);
         find = new_hunt();
         writeboard(writeFD,board, &i, &j, game_number);
         if(game_number > 2){
            if(compare_hits(prev_hits, curr_hits, prev_hit_in, curr_hit_in) > 
               0){
               same_ship_strat = 1;
               prev_hit_in = 0;
               init_hit(curr_hits);
               curr_hit_in = 0;
            }
            else{
               memcpy(prev_hits, curr_hits, sizeof(prev_hits));
               prev_hit_in = curr_hit_in;
               init_hit(curr_hits);
               curr_hit_in = 0;
            }
         }
         
         else{
            memcpy(prev_hits, curr_hits, sizeof(prev_hits));
            prev_hit_in = curr_hit_in;
            init_hit(curr_hits);
            curr_hit_in = 0;
         }
      }
         
      else if(signal == SHOT_REQUEST){
         if(same_ship_strat == -1){
            update_PDF(my_shots, cell_arr, &find);
            memcpy(buffer, my_shots, sizeof(buffer));
            qsort(buffer, SIZE * SIZE, sizeof(PDFshot), sort_by_freq);
            currshot.row = buffer[0].row;
            currshot.col = buffer[0].col;
            sendshot(&currshot,writeFD);
         }
         else{
            ind = prev_hits[prev_hit_in];
            currshot.row = cell_arr[ind].row;
            currshot.col = cell_arr[ind].col;
            prev_hit_in++;
            sendshot(&currshot,writeFD);
         }
      }
      
      else if(signal == SHOT_RESULT){
         read(readFD,&signal,sizeof(int));
         
         if((res = insert_shot_res(cell_arr, signal, currshot)) != -1){
            curr_hits[curr_hit_in] = (currshot.row * 10) + currshot.col;
            curr_hit_in++;
         }
         else if(same_ship_strat == 1)
            same_ship_strat = -1;
         
         create_new_pdf(my_shots);
      }

      else if(signal == OPPONENTS_SHOT)
         read(readFD,&opp_shot,sizeof(Shot));

      else if(signal == MATCH_OVER)
         break;
   }
}
 
int main(int argc, char **argv){
   int readFD = 0, writeFD = 0, signal = 0;
   char board[SIZE][SIZE];
   if (argc != 3)
   {
      fprintf(stderr, "Usage: child readFD writeFD\n");
      exit(EXIT_FAILURE);
   }
   
   readFD = getFD(argv[1]);
   writeFD = getFD(argv[2]);
   
   logic(readFD,writeFD, board, signal);
   
   return 0;
}      
