#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "cmdline.h"
#include "battleship.h"
#include "playerstats.h"
#include "gamelogic.h"
#include "h2p.h"

/* this function will run the game logic with the prints needed 
 * if the -d flag is used 
 */

void outerlogic(int shotcount, int toP1W, int toP2W, int fromP1R ,
   int fromP2R, int num_games, int dflag, Player *p1, Player *p2){
   int roundnum = 1, gameno = 1;
   while(roundnum <= num_games){
      innerlogic(shotcount,toP1W, toP2W, fromP1R, fromP2R, &roundnum
         ,dflag, p1,p2);
      if((*p1).sunk == NUMBER_OF_SHIPS || (*p2).sunk == NUMBER_OF_SHIPS){
         printgameres(p1,p2,dflag, gameno++);
      }
      else{
         (*p1).losses = (*p1).losses + 1;
         (*p2).losses = (*p2).losses + 1;
         nowinnerprint(gameno++, p1, p2, dflag);
      }   
   }
}

/* this is a helper fuction for outerlogicD
 * it will control a game and return the results
 */

void innerlogic(int shotcount, int toP1W, int toP2W, int fromP1R, int fromP2R 
   ,int *roundnum, int dflag, Player *p1, Player *p2){
   int totsh = 0, tot = 0;
   resetplayer(p1); 
   resetplayer(p2);
   if(dflag == 1)
      fprintf(stdout,"\nGame %d Details:\n", *roundnum);
   *roundnum = *roundnum + 1;
   start_game(toP1W,fromP1R, toP2W, fromP2R, p1, p2, &tot);
   if (tot == SIZE * SIZE){
      while(totsh < MAX_SHOTS){
         shot_logic(toP1W, fromP1R, toP2W, fromP2R, p1,p2, dflag, &totsh);
      }
   }
   
   if((*p1).sunk == NUMBER_OF_SHIPS || (*p2).sunk == NUMBER_OF_SHIPS)
      updaterec(p1,p2); 
}

/* helper function that sends the New_Game signal which 
 * will then lead to the retrieval of the locations of the ships
 * which  will be inserted into each players structure 
 */

void start_game(int toP1W, int fromP1R, int toP2W, int fromP2R, Player* p1,
   Player* p2, int *tot){
   send_sig_to_child(toP1W, NEW_GAME);
   read_board(fromP1R, p1, tot);
   if ( *tot == SIZE * SIZE){
      *tot = 0;
      send_sig_to_child(toP2W, NEW_GAME);
      read_board(fromP2R, p2, tot);
   }
}

/* helper function that will run th shot logic
 * i.e. will send SHOT_REQUEST, process SHOT,
 * send result to opp. and player
 * return (MAX_SHOTS) if early termination is needed 
 * due to the ships being sunk;
 */

void shot_logic(int toP1W, int  fromP1R, int toP2W, int fromP2R,
   Player *p1,Player *p2, int dflag, int *totsh){
   Shot currshot;
   int res = 0;
   send_sig_to_child(toP1W, SHOT_REQUEST);
   read_shot_from_child(fromP1R, &currshot);
   (*p1).shot = (*p1).shot + 1;
   res = process_shot(&currshot, p2);
   update_counts(res,p1);
   print_shot_res(p1,res, dflag, (currshot).row, (currshot).col); 
   send_sig_to_child(toP1W, SHOT_RESULT);
   send_sig_to_child(toP1W, res);
   send_sig_to_child(toP2W, OPPONENTS_SHOT);
   send_shot_to_child(toP2W, &currshot);

   send_sig_to_child(toP2W, SHOT_REQUEST);
   read_shot_from_child(fromP2R, &currshot);
   (*p2).shot = (*p2).shot + 1;
   res = process_shot(&currshot, p1);
   update_counts(res,p2); 
   print_shot_res(p2,res, dflag, (currshot).row, (currshot).col);
   send_sig_to_child(toP2W, SHOT_RESULT);
   send_sig_to_child(toP2W, res);
   send_sig_to_child(toP1W, OPPONENTS_SHOT);
   send_shot_to_child(toP1W, &currshot);

   if((*p1).sunk == NUMBER_OF_SHIPS || (*p2).sunk == NUMBER_OF_SHIPS)
      *totsh = MAX_SHOTS;
   else
      *totsh = *totsh + 1;
}

/* This function processes a shot and returns MISS, HIT, or SUNK 
 */

int process_shot(Shot *currshot, Player *p){
   unsigned short row = (*currshot).row, col = (*currshot).col;
   int res = 0;
   char type = 'x';
   res = get_hit(row, col, p);
   if (res == OPEN_WATER)
      return MISS;
   (*p).board[row][col] = HIT + SINK + MISS; /*Not a char val! */
   type = update_hitcounts(res, p);
   res = checksunk(p, type);
   if (res == 0)
      return SINK;
   return HIT;
}

/*this function checks each of the ships located in
 * a Player struct. If it is a hit, it will go to that 
 * ship's array and change index to 1
 * NOTE: sum of things in array = SIZE_SHIP
 * indicates a switch to ship is sunk;
 */

int get_hit(int row,int col,Player *p){
   int shiptype = 0;
   if (outofbounds(row,col))
      return OPEN_WATER;
   shiptype = (*p).board[row][col];
   return shiptype;
}

/* this function will check if the shot is  out of bounds 
 */
int outofbounds(int row, int col){
   if(row > (SIZE - 1) || col > (SIZE -1))
      return 1;
   if(row < 0 || col < 0)
      return 1;
   return 0;
}

/*helper function that decipher whether to return
 * hit or SUNK
 */

int checksunk(Player *p, char type){
   if(type == 'a')
      return (*p).achits;
   else if(type == 'b')
      return (*p).bathits;
   else if(type == 'd')
      return (*p).deshits;
   else if(type == 's')
      return (*p).subhits;
   else if(type == 'p')
      return (*p).pbhits;
   return HIT;
}

void printgameres(Player *p1,Player *p2, int dflag, int gameno){
   char winner[255];
   if (dflag == 0)
      return;
   strcpy(winner, getwinner(p1,p2));
   if (strcmp(winner,"Draw") == 0){
      printf("\nGame %d Results: %s\n%16s: %u shots, %u hits, and %u sinks\n",
         gameno, winner, (*p1).name, (*p1).shot, (*p1).hit, (*p1).sunk);
      printf("%16s: %u shots, %u hits, and %u sinks\n",(*p2).name, (*p2).shot,
         (*p2).hit, (*p2).sunk);
      return;
   }
   printf("\nGame %d Results: %s won!\n%16s: %u shots, %u hits, and %u sinks\n",
      gameno, winner, (*p1).name, (*p1).shot, (*p1).hit, (*p1).sunk);
   printf("%16s: %u shots, %u hits, and %u sinks\n",(*p2).name, (*p2).shot,
      (*p2).hit, (*p2).sunk);
}

char * getwinner(Player *p1, Player *p2){
   if ((*p1).sunk == (*p2).sunk)
      return "Draw";
   else if((*p1).sunk > (*p2).sunk)
      return (*p1).name; 
   return (*p2).name;
}

void print_shot_res(Player* p, int res, int dflag, int row, int col){
   char str[10];
   strcpy(str,convertres(res));
   if (dflag == 0)
      return;
   printf("%16s: shot[%2d][%2d], %5s, shots:%3d, misses:%2d, hits:%2d,"\
      " sunk:%d\n"
      ,(*p).name, row, col, str, (*p).shot, (*p).miss, (*p).hit, (*p).sunk);
}

char * convertres(int res){
   if (res == MISS)
      return "Miss";
   if (res == HIT)
      return "HIT!";
   return "SINK!";
}

void nowinnerprint(int gameno, Player *p1, Player *p2, int dflag){
   if(dflag == 0)
      return;
   printf("\nGame %d Results: No winner within %d shots\n",
      gameno++, MAX_SHOTS);
   printf("%16s: %u shots, %u hits, and %u sinks\n",(*p1).name,
      (*p1).shot, (*p1).hit, (*p1).sunk);
   printf("%16s: %u shots, %u hits, and %u sinks\n",(*p2).name, 
      (*p2).shot,(*p2).hit, (*p2).sunk);
}
