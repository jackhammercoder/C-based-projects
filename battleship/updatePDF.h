#ifndef UPDATEPDF_H
#define UPDATEPDF_H

#include "battleship.h"
#include "searchfor.h"
#include "PDFshot.h"

typedef struct {
   char carrier_h;
   char battleship_h;
   char sub_h;
   char des_h;
   char patrol_h;
   char carrier_v;
   char battleship_v;
   char des_v;
   char sub_v;
   char patrol_v;
   char sinkcount;
} Hunt;

/* this functino intializes a hunt structure, that is,
 * it will set all the hunt booleans to 1. A Hunt structure
 * will give up hunting a certain ship if no more spots of its
 * length can be found
*/

Hunt new_hunt();


/* this function takes in a reset PDF board, an 
* int array with all the ships that are still being 
* looked for
*/

PDFshot* update_PDF(PDFshot pdfarr[], Cell cellarr[], Hunt* find);

/* this function will "hunt" for horizontal segments of size 5
* for a carrier, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal carrier it returns -1, else it will return 
*/

int carrier_horiz(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for vertical segments of size 5
* for a carrier, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal carrier it returns -1, else it will return 
*/

int carrier_vert(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for horizontal segments of size 4
* for a battleship, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal battleship it returns -1, else it will return 
*/

int battleship_horiz(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for vertical segments of size 4
* for a battleship, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal battleship it returns -1, else it will return 
*/

int battleship_vert(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for horizontal segments of size 3
* for a three, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal three it returns -1, else it will return 
*/

int three_horiz(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for vertical segments of size 3
* for a three, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal three it returns -1, else it will return 
*/

int three_vert(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for horizontal segments of size 2
* for a patrol, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal patrol it returns -1, else it will return 
*/

int patrol_horiz(Cell cellarr[], PDFshot* pdfarr);

/* this function will "hunt" for vertical segments of size 2
* for a patrol, for every one that it finds it will increment
* the frequencies in the pdf array. If it finds absolutely no 
* spots for a horizontal patrol it returns -1, else it will return 
*/

int patrol_vert(Cell cellarr[], PDFshot* pdfarr);

int sum_hor_block(Cell cellarr[],int begin, int end, int row);

int sum_vert_block(Cell cellarr[], int begin, int end, int col);


#endif