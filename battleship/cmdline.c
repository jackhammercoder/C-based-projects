#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cmdline.h"

unsigned int processflags(int argc, char * argv[], unsigned *is_d ,unsigned *n){
   unsigned int i = 1, count = 0; /* count here is the number of non flags */
   for (; i < argc ; i++){
      isgflag(argv[i], &count, is_d, n);
   }
   return count;  
}

void isgflag(char curr[], unsigned int *count, unsigned *is_d,
   unsigned *num_game){ 
   int valid  = 0, temp = 0;
   if (strncmp(curr,"-g",2) != 0){
      isdflag(curr, count, is_d); /* here is g is just a place holder */
      return;
   }
   valid = sscanf(&curr[2], "%d", &temp);
   if(valid == 0)
      exitscript();
   if(temp <= 0)
      exitscript();
   *num_game = temp;
   return;
}

void isdflag(char curr[], unsigned int *count, unsigned *is_d){
   if (strcmp(curr, "-d") != 0){
      *count = *count + 1;
      return;
   }
   if (strlen(curr) > 2)
      exitscript();
   *is_d = 1; /* turn flag on */
   return;
}

void exitscript(){
   fprintf(stderr, "Usage: battleship [-gN|-d] player1 player2\n");
   exit(EXIT_FAILURE);
}

char * getpath(int argc, int *start, char * argv[]){
   for(; (*start) < argc; (*start)++){
      if(strncmp(argv[*start],"-",1) != 0)
         break;
   }
   return argv[*start];    
}
