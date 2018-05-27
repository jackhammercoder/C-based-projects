#include "ui.h"
#include "corelogic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int checkvalidguess(char guess[], char ans[]){
   int anslen = 0, i = 0, numexact = 0, inexact = 0;
   int *ptr = &numexact;
   char *strptr;
   anslen = strlen(ans);
   calcexact(ans,guess, ptr);
   numexact = *ptr;
   if (numexact == anslen){
      return 1;
   }
   i = 0;
   for(; i < anslen; i = i + 1){
      strptr = strchr(ans, guess[i]);
      if (strptr){
         *strptr = 'y';
         inexact = inexact + 1;
      }
   }
   printf("Nope, %d exact guesses and %d inexact guesses\n", numexact, inexact);
   return 0;
}

void getans(char ans[], long seed, long pos, char maxchar){
   int i = 0, random = 0, ascii = 0, maxletter = 0;
   char letter = 'a';
   char temp[9];
   maxletter = (int) maxchar;
   srand(seed);
   for(; i < pos ; i = i + 1){
      random = rand();
      ascii = random % (maxletter - 64);
      letter = ascii + 65;
      temp[i] = letter;
   }
   temp[pos] = '\0';
   strcpy(ans,temp);
}

void guessrun(int round, long maxpos, char maxlet, char guess[]){
   int validguess = 0;
   while(validguess < 1){
      printf("\nEnter guess %d: ", round);
      getguess(maxpos, guess);
      validguess = checkguess(guess, maxlet);
   }
}

void calcexact(char ans[], char guess[], int *numexact){
   int anslen = 0, i = 0;
   anslen = strlen(ans);
   for(; i < anslen; i = i + 1){
      if(ans[i] == guess[i]){
         guess[i] = 'z';
         ans[i] = 'y';
         *numexact = *numexact + 1;
      }
   }
}
             
