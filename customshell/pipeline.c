#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "pipeline.h"

/* parses the command line, dont think I need malloc here 
 */

int parsepipe(char** pieces, char buf[]){
   char *token, temp[1024];
   int i = 0;
   strcpy(temp, buf);
   token = strtok(buf,"|");   
   while(token != NULL){
      if(i >= 20)
         return exitscript("Too Many Commands"); 
      if(invalid(token))
         return exitscript("Invalid Pipe");
      pieces[i] = token;
      i++;
      token = strtok(NULL, "|");
   }
   i = checkedges(temp, &i);
   return i;   
}

/* helper function for parsepipe
 * determines is a token is valid
 */

int invalid(char * token){
   int i = 0;
   for(; i < strlen(token); i++){
      if(!isspace(token[i]))
         return 0;
   }
   return 1;
}

int checkedges(char buf[], int* i){
   if (buf[0] == '|')
      return exitscript("Invalid Pipe");
   if (buf[strlen(buf) - 1] == '|')
      return exitscript("Invalid Pipe");
   return *i;
}

int checkpieces(char** pieces, int num_cmds){
   int i = 0, invalid = 0;
   char temp[1024];
   for(; i < num_cmds ; i++){
      strcpy(temp, pieces[i]);
      if((invalid = invalidpiece(temp)) < 0)
         break;
   }
   return invalid;
}

int invalidpiece(char * cmdpiece){
   char *token, command[1024];
   int redir = 0, i = 0;
   if(strchr(cmdpiece, '<') != NULL)
      redir++;
   if(strchr(cmdpiece, '>') != NULL)
      redir++;
   token = strtok(cmdpiece, " ");
   while(token != NULL){
      if(strncmp(token, "<", 1) != 0 && strncmp(token, ">", 1) != 0)
         i++;
      if (i == 1)
         strcpy(command, token);
      token = strtok(NULL, " ");
   }
   if(i > 11){
      fprintf(stdout, "cshell: %s: Too many arguments\n", command);
      return -1;
   }
   if(i > redir)
      return 0;
   return exitscript("Invalid Pipe");
}

/* this is the generic exit message for multiple errors
 * that occure 
 */

int exitscript(const char * message){
   fprintf(stdout, "cshell: %s\n", message);
   return -1;
}
