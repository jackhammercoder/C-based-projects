#ifndef CMDLINE_H
#define CMDLINE_H

unsigned int processflags(int argc, char * argv[], unsigned *is_d, unsigned *n);
void isgflag(char curr[], unsigned int *count, unsigned *is_d, unsigned *num_game);
void isdflag(char curr[], unsigned int *count, unsigned *is_d);
void exitscript();
char * getpath(int argc, int *start, char * argv[]);
#endif
