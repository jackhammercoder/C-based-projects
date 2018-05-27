#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "battleship.h"
#include "playerstats.h"

void outerlogic(int shotcount, int toP1W, int toP2W, int fromP1R ,
   int fromP2R, int num_games, int dflag, Player *p1, Player *p2);

void innerlogic(int shotcount, int toP1W, int toP2W, int fromP1R, int fromP2R
   ,int *roundnum, int dflag, Player *p1, Player *p2);

void start_game(int toP1W, int fromP1R, int toP2W , int fromP2R, Player* p1,
   Player* p2, int *tot);

void shot_logic(int toP1W, int  fromP1R, int toP2W, int fromP2R,
   Player *p1,Player *p2, int dflag, int *totsh);

int process_shot(Shot *currshot, Player *p);

int get_hit(int row,int col,Player *p);

int outofbounds(int row, int col);

int checksunk(Player *p, char type);

void printgameres(Player *p1,Player *p2, int dflag, int gameno);

char * getwinner(Player *p1, Player *p2);

void print_shot_res(Player* p, int res, int dflagi, int row, int col);

char * convertres(int res);

void nowinnerprint(int gameno, Player *p1, Player *p2, int dflag);
#endif



