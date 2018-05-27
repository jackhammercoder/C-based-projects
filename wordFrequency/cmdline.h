#ifndef CMDLINE_H
#define CMDLINE_H

unsigned int processflags(int argc, char * argv[], unsigned *n);
void isvalidflag(char curr[], unsigned* count, unsigned *n);
void exitscript();
FILE* getfile(char *filename, FILE* file);
void redirstdin(FILE* tempptr);
#endif
