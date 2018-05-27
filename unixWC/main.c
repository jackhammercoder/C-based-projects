#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdline.h"
#include "counting.h"

int main(int argc, char * argv[]){
   int n = 0, i = 1,failure = 0; 
   FILEINFO currfile;
   currfile = intitfilestruct(currfile);
   currfile = processflags(currfile, argc, argv, &n);
   if (argc - n == 1){
      printfile(currfile);
      return EXIT_SUCCESS;
   }   
   for (; i < argc ; i++){
      currfile = makefilestruct(argv[i], currfile);
      currfile = filerunner(currfile,&failure);
   }
   currfile = changetototal(currfile);
   if (currfile.print > 1){
      printcounts(currfile);
   }
   return failure ? EXIT_FAILURE : EXIT_SUCCESS;
}
