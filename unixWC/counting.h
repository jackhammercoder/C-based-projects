#ifndef COUNTING_H
#define COUNTING_H
#include "cmdline.h"
FILEINFO printfile(FILEINFO file);
void redirstdin(FILE* tempptr);
unsigned int linecounter(FILE *fptr);
unsigned int wordcounter(FILE *fptr);
void wordlogic(char c, int *isvalid, unsigned int * word);
unsigned int charcounter(FILE *fptr);
void printcounts(FILEINFO file);
unsigned int * makeintarray(FILEINFO file, unsigned int arr[]);
void printlogic(FILEINFO file, unsigned int arr[]);
void printerror(FILEINFO currfile, int* failure);
FILEINFO filerunner(FILEINFO currfile, int * failure);

#endif
