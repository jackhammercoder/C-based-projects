#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "counting.h"
#include "cmdline.h"

FILEINFO printfile(FILEINFO file){
   if (strcmp(file.fname,"tempfile") == 0){
      file.file = fopen(file.fname, "w");
      redirstdin(file.file);
      fclose(file.file);
   }
   file.file = fopen(file.fname, "r");
   file.lc = linecounter(file.file);
   file.wc = wordcounter(file.file);
   file.cc = charcounter(file.file);
   file.tc = file.tc + file.cc;
   file.tw = file.tw + file.wc;
   file.tl = file.tl + file.lc;
   file.print = file.print + 1;
   printcounts(file);
   return file;
}

void redirstdin(FILE* tempptr){
   int c = 0;
   while((c = getc(stdin)) != EOF){
      putc(c,tempptr);
   }
   rewind(tempptr);
}

unsigned int linecounter(FILE *fptr){
   int c = 0;
   unsigned int linecount = 0;
   while((c = getc(fptr)) != EOF){
      if (c == '\n'){
         linecount++;
      }
   }
   rewind(fptr);
   return linecount;
}

unsigned int wordcounter(FILE *fptr){
   int isvalid = 1, c = 0;
   unsigned int word = 0;
   while((c = getc(fptr)) != EOF){
      wordlogic(c,&isvalid, &word);
   }
   rewind(fptr);
   return word;
}

void wordlogic(char c, int *isvalid, unsigned int * word){
   if(isspace(c)){
      *isvalid = *isvalid + 1;
   }
   if (*isvalid > 0 && !isspace(c) && isprint(c)){
      *isvalid = 0;
      *word = *word + 1;
   }
}

unsigned int charcounter(FILE *fptr){
   int c = 0;
   unsigned int charcount = 0;
   while((c = getc(fptr)) != EOF){
      charcount++;
   }
   rewind(fptr);
   return charcount;
}   

void printcounts(FILEINFO file){
   unsigned int arr[3];
   unsigned int *ptr; 
   if( file.cflag < 1 && file.lflag < 1 && file.wflag < 1){
      printf("%10u %10u %10u", file.lc, file.wc, file.cc);
   }
   else{ 
      ptr = makeintarray(file, arr);
      printlogic(file, ptr);
   }
   if (strcmp(file.fname, "tempfile") != 0){
      printf(" %s", file.fname);
   }
   printf("\n");
}

unsigned int * makeintarray(FILEINFO file, unsigned int arr[]){
   arr[0] = 0;
   arr[1] = 0;
   arr[2] = 0;
   if (file.lflag > 0){
      arr[0] = file.lc + 1;
   }
   if (file.wflag > 0){
      arr[1] = file.wc + 1;
   }
   if (file.cflag > 0 ){
      arr[2] = file.cc + 1;
   }
   return arr;   
}

void printlogic(FILEINFO file, unsigned int arr[]){
   int spacenum = file.cflag + file.lflag + file.wflag - 1, i = 0, valid = 0;
   for(; i < 3 ; i++){
      valid = 0;
      if (arr[i] > 0){
         printf("%10u", arr[i] - 1);
         valid = 1;
      }
      if (spacenum > 0 && valid){
         printf(" ");
         spacenum--;
      }
   }
}
      
void printerror(FILEINFO currfile, int* failure){
   fprintf(stderr,"swc: ");
   perror(currfile.fname);
   *failure = 1;
}

FILEINFO filerunner(FILEINFO currfile, int * failure){
   if(currfile.file == NULL && strncmp(currfile.fname,"-",1) != 0){
      printerror(currfile, failure);
   }
   else if(strncmp(currfile.fname,"-",1) != 0){
      currfile = printfile(currfile);
   }
   return currfile;
}
