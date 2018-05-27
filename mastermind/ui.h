#ifndef UI_H
#define UI_H

   int checkflag(char *argv[], int argc);
   void exit_program();
   long int getseed();
   void flushbuffer();
   char getmaxletter();
   int validletter(char maxchar, char testchar);
   long int getpos();
   void getguess(long brdsize, char *strptr);
   int checkguess(char guess[], char maxletter);
   long int getmaxguess();
   
#endif
  
        

