#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdline.h"

int exit_script(){
   fprintf(stderr, "Usage: lzwCompress [-rN] file\n");
   fprintf(stderr, "Where: N is a number from 9 to 15 specifying"\
      " the recycle code as a power of 2\n");
   return EXIT_FAILURE;
}

int setup_Rec(char* N, char filename[], char* argv[]){
   char *currarg = NULL;
   int second = 0;
   if((currarg = strstr(argv[1], "-r")) == NULL){
      strcpy(filename , argv[1]);
      second = 1;
   }
   else if(scanin(N, currarg) == -1)
      return -1;
   currarg = strstr(argv[2], "-r");
   if(currarg == NULL && second == 1)
      return -1;
   else if(second == 1){
      if(scanin(N, currarg) == -1)
         return -1;  
   }
   else if(second == 0)
      strcpy(filename , argv[2]);
   return 0;
}

/* helper function 
 *
 */

int scanin(char *N, char *currarg){
   int scanret = 0, tempN = 0;
   if((scanret = sscanf(&currarg[2], "%d", &tempN)) == EOF){
      return -1;
   }
   else if(tempN > 15 || tempN < 9){
      return -1;
   }
   *N = tempN;
   return 1;    
}
