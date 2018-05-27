#include <stdlib.h>
#include <stdio.h>
#include "bitpacker.h"

/* Function will pack bits and then write them to the output file
 *it takes a pointer to the current unisgned short being written
 *as well as the excess and rem from the last calls.
 */

void packbits_write(unsigned short curr, unsigned short *extra,
   unsigned short *leftover, FILE* output , char recNo){
   unsigned short write = 0;
   write = (curr >> *leftover) | *extra;
   *extra = curr << (8 - *leftover);
   fprintf(output, "%c", write); 
   if(*leftover >= 8){
      write = curr >> (*leftover - 8);
      fprintf(output, "%c", write);
      *extra = curr << (16 - *leftover);
      *leftover = (*leftover + recNo - 8) % recNo;
   }
   *leftover = (*leftover + recNo - 8) % recNo;
}

/* this is a helper function to calculator to calculate
 * the 2 ^recNo value based on the recycle number
 */

unsigned short math_pow(unsigned base, unsigned power){
   int i = 1;
   unsigned ans = base;
   for(; i < power; i++){
      ans = ans * base;
   }
   return ans;
}

void trailwrite(unsigned short *extra, unsigned short *leftover, FILE* output,
   char recNo ){
   unsigned short write = 0;
   if(*extra == 0)
      return;
   write = (0 >> *leftover) | *extra;
   *extra = 0 << (8 - *leftover);
   fprintf(output, "%c",write);
}
