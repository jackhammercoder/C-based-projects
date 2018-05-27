#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "h2p.h"
#include "battleship.h"
#include "playerstats.h"

/* sends int signals to the player 
 */

void send_sig_to_child(int fd, int signal){
   int size = sizeof(int), buf = 0 ;
   buf = signal;
   if (size != write(fd, &buf, size)){
      failedwrite(__LINE__);
   }
}

/*send a shot to a child 
 */

void send_shot_to_child(int fd, Shot* sh){
   int size = sizeof(Shot);
   if (size != write(fd, sh, size)){
      failedwrite(__LINE__);
   }
}

/*reads in the shot from a child 
 */

void read_shot_from_child(int fd, Shot* sh){
   int size = sizeof(Shot); 
   read(fd, sh, size);
}

/* read in the gameboard from the child process
 *  row by row
 */

void read_board(int fd, Player *p, int *tot){
   int i = 0 , j = 0;
   for(; i < SIZE; i++){
      j = 0;
      for(; j < SIZE; j++){
         if (sizeof(char) != read(fd, &((*p).board[i][j]), sizeof(char)))
            failedread(__LINE__);
         (*tot) = *tot + 1;
      }
   }
}

/* function that processes the shot a player sends
 * will need helper function is_inbounds for auto miss
 * also needs is_sunk helper function
 * always returns hit if duplicate 
 * returns HIT MISS OR SINK depending on the result
 */

/*helper function to print pipe read error 
 */

void failedread(int line){
   fprintf(stderr, "read failure in %s at line %d\n", __FILE__ , line);
   exit(EXIT_FAILURE);
}

/*helper function to print pipe write error 
 */

void failedwrite(int line){
   fprintf(stderr, "write failure in %s at line %d\n", __FILE__ , line);
   exit(EXIT_FAILURE);
}
