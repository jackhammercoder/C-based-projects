#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "corelogic.h"

int main(int argc, char *argv[]){
   long maxpos = 0, numguess = 0, seed = 0;
   int gameover = 0, tflag = 0, round = 0;
   char maxlet = 'a';
   char tempans[9], ans[9] , guess[9];
   char ovr[] = "\nGame over, you ran out of guesses. Better luck next time!\n";
   if (argc > 1){ 
      tflag = checkflag(argv, argc);
   }
   seed = getseed();
   maxlet = getmaxletter();
   maxpos = getpos();
   numguess = getmaxguess();
   getans(ans, seed, maxpos, maxlet);
   if (tflag > 0){
      printf("Initialized Game Board: %s\n", ans);
   }
   while(gameover < 1){
      round = round + 1;
      if (round > numguess){
         printf(ovr);
         return 0;
      }
      guessrun(round, maxpos, maxlet, guess);
      strcpy(tempans,ans);
      gameover = checkvalidguess(guess,tempans);
   }
   printf("\nWow, you won in %d guesses - well done!\n", round); 
   return 0; 
}
