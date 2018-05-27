#ifndef GETWORD_H
#define GETWORD_H
#include <stdio.h>

int getWord(char **word, unsigned *wordLength, FILE* file,
   const char *fileNamei, unsigned *tot);
int wordlogic(FILE* file,char **word, int c, int *valid,
    unsigned *wordLength, unsigned *tot);
void checkalloc(char * word);
#endif
