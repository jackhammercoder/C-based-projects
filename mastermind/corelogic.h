#ifndef CORELOGIC_H
#define CORELOGIC_H

   int checkvalidguess(char guess[], char ans[]);
   void getans(char ans[],long seed, long pos, char maxletter);
   void guessrun(int round, long maxpos, char maxlet, char guess[]);
   void calcexact(char ans[], char guess[], int *numexact);
#endif
