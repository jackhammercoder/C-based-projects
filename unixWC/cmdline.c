#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cmdline.h"

FILEINFO processflags(FILEINFO file, int argc, char * argv[], int *n){
   int i = 1;
   for (; i < argc ; i++){
      file = isvalidflag(argv[i], file, n);
   }
   return file;  
}

FILEINFO isvalidflag(char curr[], FILEINFO file, int *n){ 
   if (curr[0] != '-'){
      return file;
   }
   else if (strcmp(curr,"-c") == 0){
      file.cflag = 1;
   }
   else if (strcmp(curr,"-w") == 0){
      file.wflag = 1;
   }
   else if (strcmp(curr,"-l") == 0){
      file.lflag = 1;
   }
   else{
      exitscript(curr);
   } 
   *n = *n + 1;
   return file;
}

void exitscript(char curr[]){
   fprintf(stderr, "swc: invalid option: '%s'\n",curr);
   fprintf(stderr, "Usage: swc [-l|-w|-c]... [file]...\n");
   exit(EXIT_FAILURE);
}

FILEINFO makefilestruct(char * filename, FILEINFO currfile){
   currfile.file = fopen(filename, "r");
   strcpy(currfile.fname, filename);
   return currfile;
}

FILEINFO intitfilestruct(FILEINFO file){
   strcpy(file.fname, "tempfile");
   file.cflag = 0;
   file.wflag = 0;
   file.lflag = 0;
   file.tc = 0;
   file.tw = 0;
   file.tl = 0;
   file.print = 0;
   return file;
}

FILEINFO changetototal(FILEINFO currfile){
   strcpy(currfile.fname, "total");
   currfile.cc = currfile.tc;
   currfile.wc = currfile.tw;
   currfile.lc = currfile.tl;
   return currfile;
}

