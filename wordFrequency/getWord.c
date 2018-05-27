#include <stdlib.h>
#include <stdio.h>
#include "getWord.h"
#include <ctype.h>

int getWord(char **word, unsigned *wordLength, FILE* file,
   const char *fileName, unsigned *tot){ 
   int c = 'l', valid = 0, d = 5;
   *wordLength = 0; 
   while(1)
      if ((d = wordlogic(file,word,c,&valid,wordLength, tot)) != 5)
         return d;       
}

int wordlogic(FILE* file,char **word, int c, int *valid,
   unsigned *wordLength, unsigned *tot){
   c = getc(file);
   c = tolower(c);
   if (c == EOF && *valid)
      return EOF;
   else if(c == EOF && (*valid) == 0){
      *wordLength = 0;
      return EOF;
   }
   if(isspace(c) && *valid ){
      *tot = *tot + 1;
      return 0;
   }
   else if(isspace(c) && (*valid) == 0){
      *wordLength = 0;
      return 5;
   }
   if (*wordLength == 0){
      *word = (char *) malloc(sizeof(char));
   }
   else{
      *word = (char *) realloc(*word, sizeof(char) * (*wordLength + 1)); 
   }
   checkalloc(*word);
   (*word)[*wordLength] = c;
   *wordLength = *wordLength + 1;
   if(isprint(c)){
      *valid = 1;
   }
   return 5;
}

void checkalloc(char * word){
   if(word == NULL){
      perror("wf");
      exit(EXIT_FAILURE);
   }
}
