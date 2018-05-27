#ifndef CMDLINE_H
#define CMDLINE_H
   /* this will return the amount of valid flags if applicable */
   typedef struct
   {
      FILE* file;
      char fname[256];
      int lflag;
      int wflag;
      int cflag;
      unsigned int lc;
      unsigned int wc;
      unsigned int cc;
      unsigned int tc;
      unsigned int tw;
      unsigned int tl;
      int print;
   } FILEINFO;
   FILEINFO processflags(FILEINFO file, int argc, char * argv[], int *n);
   FILEINFO isvalidflag(char curr[],FILEINFO file, int *n);
   void exitscript(char curr[]);
   FILEINFO makefilestruct(char * filename, FILEINFO currfile);
   FILEINFO intitfilestruct(FILEINFO file);
   FILEINFO changetototal(FILEINFO currfile);
#endif
