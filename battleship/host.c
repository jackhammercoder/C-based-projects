#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "cmdline.h"
#include "battleship.h"
#include "playerstats.h"
#include "h2p.h"
#include "gamelogic.h"

/* could possibly make two function for this if needed 
 */

static void init_pipes(int *p){
   if(pipe(p) < 0){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
}

/* closes read and write end of a specified pipe 
 */
static void close_pipes(int *fd){
   close(fd[0]);
   close(fd[1]);
}

static char * matchwinner(Player *p1, Player *p2){
   if ((*p1).wins == (*p2).wins)
      return "Draw";
   else if((*p1).wins > (*p2).wins)
      return (*p1).name;
   return (*p2).name;
}

static void printmatchres(Player p1, Player p2, int numgame){
   char winner[255];
   strcpy(winner, matchwinner(&p1,&p2));
   if(strcmp(winner, "Draw") == 0)
      printf("\nMatch Results: No winner in %d games", numgame);
   else
      printf("\nMatch Results: %s won!", winner);
   printf("\n%16s: %u wins, %u draws, and %u losses",
      p1.name, p1.wins, p1.draws, p1.losses); 
   printf("\n%16s: %u wins, %u draws, and %u losses\n",
      p2.name, p2.wins, p2.draws, p2.losses);
}

char * getname(char name[]){
   char *str;
   str = strrchr(name, '/');
   if(str == NULL)
      return name;
   return ++str;
}

int main(int argc, char * argv[]){
   unsigned numgame = 3, show_d = 0, nonflag = 0;
   int fromP2[2], toP2[2], fromP1[2], toP1[2], shot_count = 0, result = 0;
   int start = 1;
   char p2read[6], p2write[6], p1read[6], p1write[6], name1[256], name2[256];
   pid_t pidp1, pidp2;
   Player p1, p2;
   p1 = init_stats();
   p2 = init_stats();
   nonflag = processflags(argc, argv, &show_d, &numgame);
   if (nonflag != 2)
      exitscript();
   strcpy(name1,getpath(argc, &start, argv));
   start++;
   strcpy(name2 ,getpath(argc, &start, argv));
   
   strcpy(p1.name, getname(name1));
   strcpy(p2.name, getname(name2));
   init_pipes(fromP2);  
   init_pipes(toP2);  
   init_pipes(fromP1);  
   init_pipes(toP1);

   sprintf(p2read, "%d", toP2[0]);
   sprintf(p2write, "%d", fromP2[1]);
   sprintf(p1read, "%d", toP1[0]);
   sprintf(p1write, "%d", fromP1[1]);

   if ((pidp1 = fork()) < 0)
      exit(EXIT_FAILURE);
   else if(pidp1  == 0)
      execl(name1, name1, p1read, p1write, (char *)0);
   
   if ((pidp2 = fork()) < 0)
      exit(EXIT_FAILURE);
   else if(pidp2  == 0)
      execl(name2, name2, p2read, p2write, (char *)0);
   outerlogic(shot_count, toP1[1], toP2[1],fromP1[0], fromP2[0],
      numgame, show_d, &p1, &p2);    
   send_sig_to_child(toP1[1], MATCH_OVER);
   waitpid(pidp1, &result, 0);
   send_sig_to_child(toP2[1], MATCH_OVER);
   waitpid(pidp2, &result, 0);
   printmatchres(p1,p2, numgame);
   close_pipes(fromP2);  
   close_pipes(toP2);  
   close_pipes(fromP1);  
   close_pipes(toP1); 
   return 0;   
} 
