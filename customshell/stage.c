#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "pipeline.h"
#include "stage.h"

Stage init_stage(){
   Stage s;
   strcpy(s.inputname, "stdin") ;
   strcpy(s.outputname, "stdout");
   s.argv[0] = NULL;
   s.arg_num = 0;
   return s;
}

/* This will create a list of stages seperated by pipelines
 */
Stage getstage(char** pipepieces, int i){
   char temp[1024];
   Stage s;
   strcpy(temp, pipepieces[i]);
   s = init_stage();
   s = fillStage(temp, s);
   /* fprintf(stderr, "Command when setup %d: [%s]\n", i, s.argv[0]); */

   return s;
}

Stage fillStage(char * temp, Stage s){
   char* tokens_arr[1025], *curr = NULL;
   int num_tokens = 0, i = 0, arg_num = 0;
   fill_tok_arr(tokens_arr, &num_tokens, temp);
   for(; i < num_tokens ; i++){
      curr = tokens_arr[i];
      if(strcmp(curr, "<") == 0)
         strcpy(s.inputname, tokens_arr[++i]);
      else if(strcmp(curr, ">") == 0)
         strcpy(s.outputname , tokens_arr[++i]);
      else if(arg_num <= 10){
         s.argv[arg_num] =  curr;
         s.arg_num = s.arg_num + 1;
         arg_num++;
      }
   }
   s.argv[11] = '\0';
   return s;
}

/* this funtion will fill a token array (like a queue) 
 * with all the whitespace delimited thangs
 */

void fill_tok_arr(char** tokens_arr, int *num_tokens, char * str){
   char *token;
   token = strtok(str, " ");
   while(token != NULL){
      tokens_arr[*num_tokens] = token;
      *num_tokens = *num_tokens + 1;
      token = strtok(NULL, " ");
   }
}

