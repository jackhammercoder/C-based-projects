#include <stdlib.h>
#include "playerstats.h"
#include "battleship.h"
Player init_stats(){
   Player p;
   p.miss = 0;
   p.sunk = 0;
   p.hit = 0;
   p.shot = 0;
   p.wins = 0;
   p.draws = 0;
   p.losses = 0;
   p.achits = SIZE_AIRCRAFT_CARRIER;
   p.bathits = SIZE_BATTLESHIP;
   p.deshits = SIZE_DESTROYER;
   p.subhits = SIZE_SUBMARINE;
   p.pbhits = SIZE_PATROL_BOAT;
   return p;
}

void resetplayer(Player *p){
   (*p).miss = 0;
   (*p).sunk = 0;
   (*p).hit = 0;
   (*p).shot = 0;
   (*p).achits = SIZE_AIRCRAFT_CARRIER;
   (*p).bathits = SIZE_BATTLESHIP;
   (*p).deshits = SIZE_DESTROYER;
   (*p).subhits = SIZE_SUBMARINE;
   (*p).pbhits = SIZE_PATROL_BOAT;
}

void updaterec(Player *p1,Player *p2){
   if ((*p1).sunk > (*p2).sunk){
      (*p1).wins = (*p1).wins + 1;
      (*p2).losses = (*p2).losses + 1;
   }
   else if ((*p2).sunk > (*p1).sunk){
      (*p2).wins = (*p2).wins + 1;
      (*p1).losses = (*p1).losses + 1;
   }
   else{
      (*p2).draws = (*p2).draws + 1;
      (*p1).draws = (*p1).draws + 1;
   }
}

void update_counts(int res, Player *p){
   if(res == MISS)
      (*p).miss = (*p).miss + 1;
   else if(res == SINK){
      (*p).sunk = (*p).sunk + 1;
      (*p).hit = (*p).hit + 1;
   }
   else
      (*p).hit = (*p).hit + 1;
}

/* function that updated ships if one of the macros 
 * representing a shiptype is read in
 */

char update_hitcounts(int hittype, Player *p){
   char type = 'x';
   type = shiptype(hittype);
   if(type == 'a')
      (*p).achits = (*p).achits - 1;
   else if(type == 'b')
      (*p).bathits = (*p).bathits - 1;
   else if(type == 'd')
      (*p).deshits = (*p).deshits - 1;
   else if(type == 's')
      (*p).subhits = (*p).subhits - 1;
   else if(type == 'p')
      (*p).pbhits = (*p).pbhits - 1;
   return type;
}

/*helper function that identifies the ship type a certain 
 * macro int that is passed in 
 */

char shiptype(int ship){
   if(ship == AIRCRAFT_CARRIER)
      return 'a';
   else if(ship == BATTLESHIP)
      return 'b';
   else if(ship == DESTROYER)
      return 'd';
   else if(ship == SUBMARINE)
      return 's';
   else if(ship == PATROL_BOAT)
      return 'p';
   return 'x';
}
