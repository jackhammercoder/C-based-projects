#ifndef H2P_H
#define H2P_H
#include "battleship.h"
#include "playerstats.h"

/* a signal can be any of the macros
 * this controls the game flow by sending NEW_GAME, SHOT_REQUEST
 * etc
 */
void send_sig_to_child(int fd, int signal);

/*send a shot structure to a to a child */

void send_shot_to_child(int fd, Shot* sh);

/*reads in the shot structure from a child */

void read_shot_from_child(int fd, Shot* sh);

/* read in the gameboard from the child process
 * row by row
 */

void read_board(int fd, Player* p, int *tot);

void failedread(int line);

void failedwrite(int line);
#endif
