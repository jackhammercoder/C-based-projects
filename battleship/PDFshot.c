#include <stdio.h>
#include "PDFshot.h"
#include "battleship.h"

int sort_by_freq(const void* pdfshot1, const void* pdfshot2){
   PDFshot *pdf1, *pdf2;
   
   pdf1 = (PDFshot*) pdfshot1;
   pdf2 = (PDFshot*) pdfshot2;

   if(pdf1->freq == pdf2->freq){
      return 0;
   }
   else if(pdf1->freq < pdf2->freq){
      return 1;
   }
   return -1;
}

void create_new_pdf(PDFshot* my_shots){
   int row = 0, col = 0, index = 0;
   
   for(; row < SIZE; row++){
      col = 0;
      for(; col < SIZE; col++){
         my_shots[index++] = new_shotPDF(row, col);
      }
   }
}

PDFshot new_shotPDF(int row, int col){
   PDFshot pshot;
   pshot.row = row;
   pshot.col = col;
   pshot.freq = 0;
   return pshot;
}
