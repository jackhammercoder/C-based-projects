#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "getWord.h"
#include "cmdline.h"
#include "tree.h"

static void printWord(char *word, unsigned int len){
   int i = 0;
   for(; i < len && i < 30 ; i++){
      if(isprint(word[i]))
         printf("%c", word[i]);
      else
         printf("%c", UCHAR_MAX);
   }
   if(len > 30)
      printf("...");
   printf("\n");
}

static void printresults(struct Node **arr,unsigned num, 
   unsigned uni, unsigned tot){
   int i = 0;
   printf("%u unique words found in %u total words\n", uni, tot);
   for(; i< num; i++){
      printf("%10u - ", arr[i]->count);
      printWord(arr[i]->word, arr[i]->len);
   }
}

int freqcomp(const void *node1, const void *node2){
   struct Node *n1, *n2;
   n1 = *(struct Node**) node1;
   n2 = *(struct Node**) node2;
   if(n1->count == n2->count)
      return compareNew(n1,n2->word, n2->len);
   if (n1->count < n2->count)
      return 1;
   return -1;
}

int main(int argc, char * argv[]){
   unsigned int numprints = 0, len = 0, i = 1, uni = 0, tot = 0,n = 0;
   FILE* file = NULL;
   char *word = NULL;
   struct Node *root = NULL;
   struct Node **arr = NULL;
   numprints = processflags(argc, argv, &n);
   if (numprints == 0)
      numprints = 10;
   if((argc - n) < 2){
      file = fopen("tempfile","w");
      redirstdin(file);
      fclose(file);
      file = getfile("tempfile",file);
      while(EOF != getWord(&word, &len, file, "tempfile", &tot)){
         root = insert(root,word,len, &uni);
      }
      if(len != 0){
         tot = tot + 1;
         root = insert(root,word,len,&uni);
      }
      fclose(file);
   }
   for(; i < argc; i++){
      if((file = getfile(argv[i], file)) == NULL)
         continue;
      while(EOF != getWord(&word, &len, file, argv[i], &tot)){
         root = insert(root,word,len, &uni);
      }
      if(len != 0){
         tot = tot + 1;
         root = insert(root,word,len, &uni);
      }
      fclose(file);
   }
   arr = (struct Node**)malloc(sizeof(struct Node*) * uni);
   if(arr == NULL){
      perror("wf");
      exit(EXIT_FAILURE);
   } 
   treedump(root, arr, 0);
   qsort(arr,uni,sizeof(struct Node**),freqcomp);
   if(numprints > uni)
      numprints = uni;
   printresults(arr, numprints, uni, tot);
   deallocate(arr, uni);
   return EXIT_SUCCESS;
}
