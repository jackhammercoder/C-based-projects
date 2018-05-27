#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cmdline.h"

unsigned int processflags(int argc, char * argv[], unsigned *n){
   unsigned int i = 1, count = 0;
   for (; i < argc ; i++){
      isvalidflag(argv[i], &count, n);
   }
   return count;  
}

void isvalidflag(char curr[], unsigned int *count, unsigned *n){ 
   int valid  = 0;
   *count = 0;
   if (curr[0] != '-')
      return;
   else if (strncmp(curr,"-n",2) == 0){
      valid = sscanf(&curr[2],"%u",count);
      if(valid < 0 || *count == 0)
         exitscript();
      *n = *n + 1;
      return;
   }
   exitscript();
}

void exitscript(){
   fprintf(stderr, "Usage: wf [-nX] [file...]\n");
   exit(EXIT_FAILURE);
}

FILE* getfile(char *filename, FILE *file){
   if (filename[0] == '-')
      return NULL;
   file = fopen(filename, "r");
   if (file == NULL){
      fprintf(stderr,"wf: ");
      perror(filename);
      exit(EXIT_FAILURE);
   }
   return file;
}

void redirstdin(FILE* tempptr){
   int c = 0;
   while((c = getc(stdin)) != EOF){
      putc(c,tempptr);
   }
   rewind(tempptr);
}
