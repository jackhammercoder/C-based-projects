#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include "battleship.h"

typedef struct{
   char name[255];
   unsigned miss;
   unsigned sunk;
   unsigned hit;
   unsigned shot;
   unsigned wins;
   unsigned draws;
   unsigned losses;
   int achits;
   int bathits;
   int deshits;
   int subhits;
   int pbhits;
   char board[SIZE][SIZE];
}Player;

Player init_stats();
void resetplayer(Player *p);
void updaterec(Player *p1, Player *p2);
void update_counts(int res, Player *p);
Player update_ships(int row, int col, int ship, Player p);
char shiptype(int ship);
char update_hitcounts(int hittype, Player *p);
#endif
