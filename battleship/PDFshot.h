#ifndef PDFSHOT_H
#define PDFSHOT_H


typedef struct{
   unsigned short row;
   unsigned short col;
   int freq;
} PDFshot;

int sort_by_freq(const void* pdfshot1, const void* pdfshot2);

void create_new_pdf(PDFshot* my_shots);

PDFshot new_shotPDF(int row, int col);

void print_PDF(PDFshot* my_shots);

#endif
