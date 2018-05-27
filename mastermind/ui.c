#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int checkflag(char *argv[], int argc){
   char flag[6] = "-show";
   int trueflag = 0;
   if (argc == 2){
      trueflag = strcmp(flag,argv[1]);
      if (trueflag == 0){
         return 1;
      }
      exit_program();
   }
   exit_program();
   return 0;
}   

void exit_program(){
   fprintf(stderr, "Usage: mastermind [-show]\n");
   exit(EXIT_FAILURE);
}

long getseed(){
   long seed = 0;
   printf("Enter the seed for random number generation: ");
   while (scanf("%ld", &seed) != 1){
      flushbuffer();
      printf("Seed must be an integer value, please try again\n");
      printf("Enter the seed for random number generation: ");
   }
   flushbuffer();
   if (seed > INT_MAX){
      seed = INT_MAX;
   }
   if (seed < INT_MIN){
      seed = INT_MIN;
   }
   return seed;
}  

void flushbuffer(){
   char ch;
   while((ch=getchar()) != EOF && ch!='\n');
}

char getmaxletter(){
   char maxlet = 'A', test = 'Z';
   int  valid2 = 0;
   printf("Enter the maximum letter for the game (A-Z): ");
   scanf("%c", &maxlet);
   flushbuffer();
   valid2 = validletter(test,maxlet);
   while(valid2 < 1 ){
      printf("The letter must be an uppercase A-Z, please try again\n");
      printf("Enter the maximum letter for the game (A-Z): ");
      scanf("%c", &maxlet);
      flushbuffer();
      valid2 = validletter(test,maxlet);
   }
   return maxlet;
}

int validletter(char maxchar, char testchar){
   if (testchar <= maxchar && testchar >= 'A'){
      return 1;
   }
   return 0;
}

long getpos(){
   long pos = 0; 
   int valid = 0;
   while(valid < 1){
      printf("Enter the number of positions for the game (1-8): ");
      scanf("%ld", &pos);
      flushbuffer(); 
      if (pos <= 8 && pos >= 1){
         break;
      }
      printf("The number of positions must be 1-8, please try again\n");
   }
   return pos;
}

long getmaxguess(){
   long int max = 0;
   int valid = 0;
   printf("Enter the number of guesses allowed for the game: ");
   valid = scanf("%ld", &max);  
   flushbuffer();
   while(max <= 0 || valid < 1){
      printf("The number guesses must be a positive " 
         "integer, please try again\n"); 
      printf("Enter the number of guesses allowed for the game: ");
      valid = scanf("%ld", &max);
      flushbuffer();
   }
   if (max > INT_MAX){
      max = INT_MAX;
   }
   if (max < INT_MIN){
      max = INT_MIN;
   } 
   return max;
}

void getguess(long brdsize, char *strptr){
   int i = 0; 
   long arraysize = 0;
   char posguess[9];
   char letter = 'A';
   arraysize = brdsize + 1;
   for(; i < brdsize; i = i + 1){
      scanf(" %c", &letter);
      posguess[i] = letter;   
   }
   flushbuffer();
   posguess[brdsize] = '\0';
   strcpy(strptr,posguess);
}
int checkguess(char guess[], char maxletter){
   int length = 0, i =  0;
   length = strlen(guess);
   for (; i < length; i = i + 1){
      if ( (validletter(maxletter, guess[i])) == 0){
         printf("Invalid guess, please try again\n");
         return 0;
      }
   }
   return 1;
}   
