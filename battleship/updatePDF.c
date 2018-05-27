#include <stdio.h>
#include "battleship.h"
#include "PDFshot.h"
#include "searchfor.h"
#include "updatePDF.h"

Hunt new_hunt(){
   Hunt h;
   h.carrier_h = 1;
   h.battleship_h = 1;
   h.des_h = 1;
   h.sub_h = 1;
   h.patrol_h = 1;
   h.carrier_v = 1;
   h.battleship_v = 1;
   h.des_v = 1;
   h.sub_v = 1;
   h.patrol_v = 1;
   h.sinkcount = 0;
   return h;
}

PDFshot* update_PDF(PDFshot pdfarr[], Cell cellarr[], Hunt* find){
   
   int hor_ret = 0, vert_ret = 0;

   if(find->carrier_h > 0){
      hor_ret = carrier_horiz(cellarr, pdfarr);
      if(hor_ret == -1){
         find->carrier_h = -1;
      }
   }

   if(find->carrier_v > 0){
      vert_ret = carrier_vert(cellarr, pdfarr);
      if(vert_ret == -1){
         find->carrier_v = -1;
      }
   }

   if(find->battleship_h > 0){
      hor_ret = battleship_horiz(cellarr, pdfarr);
      if(hor_ret == -1){
         find->battleship_h = -1;
      }
   }

   if(find->battleship_v > 0){
      vert_ret = battleship_vert(cellarr, pdfarr);
      if(vert_ret == -1){
         find->battleship_v = -1;
      }
   }

   if(find->des_h > 0){
      hor_ret = three_horiz(cellarr, pdfarr);
      if(hor_ret == -1){
         find->des_h = -1;
         find->sub_h = -1;
      }
   }

   if(find->des_v > 0){
      vert_ret = three_vert(cellarr, pdfarr);
      if(vert_ret == -1){
         find->des_v = -1;
         find->sub_v = -1;
      }
   }

   if(find->sub_h > 0){
      hor_ret = three_horiz(cellarr, pdfarr);
      if(hor_ret == -1){
         find->des_h = -1;
         find->sub_h = -1;
      }
   }

   if(find->sub_v > 0){
      vert_ret = three_vert(cellarr, pdfarr);
      if(vert_ret == -1){
         find->des_v = -1;
         find->sub_v = -1;
      }
   }

   if(find->patrol_h > 0){
      hor_ret = patrol_horiz(cellarr, pdfarr);
      if(hor_ret == -1){
         find->patrol_h = -1;
      }
   }

   if(find->patrol_v > 0){
      vert_ret = patrol_vert(cellarr, pdfarr);
      if(vert_ret == -1){
         find->patrol_v = -1;
      }
   }
   return pdfarr;
}

int carrier_horiz(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, hor_num = 0;
   for(; row < SIZE ; row++){
      col = 0;
      for(; col < SIZE; col++){
         begin = col;
         end = begin + 4;
         if(end < SIZE){
            sum = sum_hor_block(cellarr, begin, end, row);
            ind = (row * 10) + col;
            if(sum == 5){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               hor_num++;   
            }
            else if(sum < 500 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               hor_num++ ;  
            }
         }
         else{
            break;
         }
      }
   }
   if(hor_num == 0){
      return -1;
   }
   return hor_num;
}

int carrier_vert(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, vert_num = 0;
   for(; col < SIZE ; col++){
      row = 0;
      for(; row < SIZE; row++){
         begin = row;
         end = begin + 4;
         if(end < SIZE){
            sum = sum_vert_block(cellarr, begin, end, col);
            ind = (begin++ * 10) + col;
            if(sum == 5){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               vert_num++;   
            }
            else if(sum < 500 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               vert_num++ ;  
            }
         }
         else{
            break;
         }
      }
   }
   if(vert_num == 0){
      return -1;
   }
   return vert_num;   
}

int battleship_horiz(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, hor_num = 0;
   for(; row < SIZE ; row++){
      col = 0;
      for(; col < SIZE; col++){
         begin = col;
         end = begin + 3;
         if(end < SIZE){
            sum = sum_hor_block(cellarr, begin, end, row);
            ind = (row * 10) + col;
            if(sum == 4){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               hor_num++;   
            }
            else if(sum < 400 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               hor_num++;   
            }
         }
         else{
            break;
         }
      }
   }
   if(hor_num == 0){
      return -1;
   }
   return hor_num;
}

int battleship_vert(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, vert_num = 0;
   for(; col < SIZE ; col++){
      row = 0;
      for(; row < SIZE; row++){
         begin = row;
         end = begin + 3;
         if(end < SIZE){
            sum = sum_vert_block(cellarr, begin, end, col);
            ind = (begin++ * 10) + col;
            if(sum == 4){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               vert_num++;   
            }
            else if(sum < 400 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               vert_num++;   
            }
         }
         else{
            break;
         }
      }
   }
   if(vert_num == 0){
      return -1;
   }
   return vert_num;
}

int three_horiz(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, hor_num = 0;
   for(; row < SIZE ; row++){
      col = 0;
      for(; col < SIZE; col++){
         begin = col;
         end = begin + 2;
         if(end < SIZE){
            sum = sum_hor_block(cellarr, begin, end, row);
            ind = (row * 10) + col;
            if(sum == 3){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               hor_num++;   
            }
            else if(sum < 300 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               hor_num++;   
            }
         }
         else{
            break;
         }
      }
   }
   if(hor_num == 0){
      return -1;
   }
   return hor_num;
}

int three_vert(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, vert_num = 0;
   for(; col < SIZE ; col++){
      row = 0;
      for(; row < SIZE; row++){
         begin = row;
         end = begin + 2;
         if(end < SIZE){
            sum = sum_vert_block(cellarr, begin, end, col);
            ind = (begin++ * 10) + col;
            if(sum == 3){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               vert_num++;   
            }
            else if(sum < 300 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               vert_num++;   
            }
         }
         else{
            break;
         }
      }
   }
   if(vert_num == 0){
      return -1;
   }
   return vert_num;
}

int patrol_horiz(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, hor_num = 0;
   for(; row < SIZE ; row++){
      col = 0;
      for(; col < SIZE; col++){
         begin = col;
         end = begin + 1;
         if(end < SIZE){
            sum = sum_hor_block(cellarr, begin, end, row);
            ind = (row * 10) + col;
            if(sum == 2){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind++;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               hor_num++;   
            }
            else if(sum < 200 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind++;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               hor_num++;   
            }
         }
         else{
            break;
         }
      }
   }
   if(hor_num == 0){
      return -1;
   }
   return hor_num;
}

int patrol_vert(Cell cellarr[], PDFshot* pdfarr){
   int row = 0 , col = 0, begin = 0, end = 0, sum = 0,
      ind = 0, vert_num = 0;
   for(; col < SIZE ; col++){
      row = 0;
      for(; row < SIZE; row++){
         begin = row;
         end = begin + 1;
         if(end < SIZE){
            sum = sum_vert_block(cellarr, begin, end, col);
            ind = (begin++ * 10) + col;
            if(sum == 2){
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               ind = (begin++ * 10) + col;
               pdfarr[ind].freq = pdfarr[ind].freq + 1;
               vert_num++;   
            }
            else if(sum < 200 && sum > 0){
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               ind = (begin++ * 10) + col;
               if(cellarr[ind].state != HIT)
                  pdfarr[ind].freq = pdfarr[ind].freq + 100;
               vert_num++;  
            }
         }
         else{
            break;
         }
      }
   }
   if(vert_num == 0){
      return -1;
   }
   return vert_num;
}

int sum_hor_block(Cell cellarr[],int begin, int end, int row){
   int sum = 0, index = 0;
   for(; begin <= end; begin++){
      index = (row * 10) + begin;
      if(cellarr[index].state == OPEN_WATER){
         sum = sum + 1;
      }
      else if(cellarr[index].state == MISS){
         return -1;
      }
      else if(cellarr[index].state == HIT){
         sum = sum + 100;
      }
      else if(cellarr[index].state == SINK){
         return -1;
      }
   }
   return sum;
}

int sum_vert_block(Cell cellarr[], int begin, int end, int col){
   int sum = 0, index = 0;

   for(; begin <= end; begin++){
      index = (begin * 10) + col;
      if(cellarr[index].state == OPEN_WATER){
         sum = sum + 1;
      }
      else if(cellarr[index].state == MISS){
         return -1;
      }
      else if(cellarr[index].state == HIT){
         sum = sum + 100;
      }
      else if(cellarr[index].state == SINK){
         return -1;
      }
   }
   return sum;
}
