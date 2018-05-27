#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "pipeline.h"
#include "stage.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void close_ends(int read, int write, int num_cmds){
   close(write);
   if(num_cmds == 1)
      close(read);
}

void flushbuffer(){
   char ch;
   while((ch=getchar()) != EOF && ch!='\n');
}

int exit_input(int read, int write){
   close_ends(read,write,1);
   return exitscript("Unable to open file for input");
}

int exit_output(int read, int write){
   close_ends(read,write,1);
   return exitscript("Unable to open file for output");
}

int redirection(char in[], char out[], int *readfd , int *writefd, 
   int read, int write){
   if(strcmp(in, "stdin") != 0){
      if((*readfd = open(in, O_RDONLY)) < 0)
         return exit_input(read,write);
   }
   if(strcmp(out, "stdout") != 0){
      if((*writefd = open(out,O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
         return exit_output(read,write);
   }
   return 0;
}

int firstcommand(char* in, char * out, char * argv[] , int read,
   int write, int num_cmds){
   pid_t pid;
   int status = 0, readfd = STDIN_FILENO, writefd = 1, 
      stdincpy = 0;
   stdincpy = dup(STDIN_FILENO);
   if(redirection(in, out ,&readfd,&writefd,read,write) < 0)
      return -1; 
   dup2(readfd, STDIN_FILENO); 
   pid = fork();
   
   if(pid == 0){
      if(num_cmds > 1)
         dup2(write , STDOUT_FILENO); 
      if (execvp(argv[0], argv) < 0){
         fprintf(stdout,"cshell: %s: Command not found\n", argv[0]);
      }
      exit(EXIT_FAILURE);
   }
   waitpid(pid, &status, 0);
   /*fprintf(stderr, "Im closing: %d and %d\n", read , write); */
   close(readfd);
   dup2(stdincpy, STDIN_FILENO);
   close(stdincpy);
   close_ends(read,write,num_cmds);
   return read;
}

int midcommand(char in[], char out[], char * argv[], int read,
   int prevread ,  int write){
   pid_t pid;
   int status = 0,  readfd = STDIN_FILENO, writefd = 1, stdincpy = 0;
   stdincpy = dup(STDIN_FILENO); 
   if(redirection(in, out ,&readfd,&writefd,read,write) < 0)
      return -1; 
   /* dup2(write,STDOUT_FILENO); */
   dup2(readfd,STDIN_FILENO);
   pid = fork();
 
   if(pid == 0){
      dup2(prevread, STDIN_FILENO);
      dup2(write, STDOUT_FILENO);
      if(execvp(argv[0], argv) < 0){
         fprintf(stdout,"cshell: %s: Command not found\n", argv[0]);
      }
      exit(EXIT_FAILURE);
   }
   waitpid(pid, &status, 0);
   /*fprintf(stderr, "Im closing: %d and %d\n", read , write); */
   close(readfd);
   dup2(stdincpy, STDIN_FILENO);
   close(stdincpy);
   close(prevread);
   close_ends(read,write,0);
   return read;
}

void endcommand(char in[], char out[], char * argv[], 
   int read, int prevread, int write){
   pid_t pid;
   int status = 0,  readfd = STDIN_FILENO, writefd = 1, stdincpy = 0;
   stdincpy = dup(STDIN_FILENO); 
   if(redirection(in, out ,&readfd,&writefd,read,write) < 0)
      return; 
   /* dup2(write,STDOUT_FILENO); */
   dup2(readfd,STDIN_FILENO);

   pid = fork();
   
   if (pid == 0){
      dup2(prevread, STDIN_FILENO);
      if(execvp(argv[0], argv) < 0){
         fprintf(stdout,"cshell: %s: Command not found\n", argv[0]);
      }
      exit(EXIT_FAILURE);
   }
   waitpid(pid, &status, 0);
   /* fprintf(stderr, "Im closing: %d and %d\n", read , write); */
   close(readfd);
   dup2(stdincpy, STDIN_FILENO);
   close(stdincpy);
   close(prevread);
   close_ends(read,write,1);
}

static void runcommands(char** pipepieces, int num_cmds){
   int fd[2], prevread = 20, i = 0, read = 9, write = 10;
   Stage temp;
   for(; i < num_cmds ; i++){
      temp = getstage(pipepieces, i); 
      pipe(fd);
      read = fd[0];
      write = fd[1];
      if(i == 0){
         prevread = firstcommand(temp.inputname, temp.outputname, 
            temp.argv, read, write, num_cmds);
      }
      else if(i < num_cmds - 1){
         prevread = midcommand(temp.inputname, temp.outputname, 
            temp.argv, read, prevread, write);
      }
      else
         endcommand(temp.inputname, temp.outputname, temp.argv,
            read, prevread, write);
      if(prevread < 0)
         break;
      /* fprintf(stderr, "---done with child process: %d-----\n", i); */
   }
}

int looplogic(char * buf, char** pipepieces){
   int num_cmds = 0;
   if (strlen(buf) > 1024)
      return exitscript("Command line too long");

   if(strcmp(buf,"exit") == 0)
      return -2;
       
   if((num_cmds = parsepipe(pipepieces, buf)) == -1)
      return -1;
      
   if(checkpieces(pipepieces, num_cmds)  == -1)
      return -1;
   return num_cmds;
}

int main(int argc, char * argv[]){
   char* pipepieces[20];
   char buf[4096];
   int num_cmds = 0;
   setbuf(stdout, NULL);

   printf(":-) ");
   while (fgets(buf, 4096, stdin) != NULL) {
      if(buf[strlen(buf) - 1] == '\n')
         buf[strlen(buf) - 1] = 0;
      num_cmds = looplogic(buf, pipepieces);

      if(num_cmds == -1){
         printf(":-) ");
         continue;
      }
      
      if(num_cmds == -2)
         return 0;

      runcommands(pipepieces, num_cmds);
   
      printf(":-) ");
   }
   printf("exit\n");
   return 0;
}
