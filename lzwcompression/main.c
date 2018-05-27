#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "cmdline.h"
#include "bitpacker.h"

typedef struct pack_info{
   unsigned short rem;
   unsigned short pow;
   unsigned short excess;
   unsigned short maxcode;
   unsigned short currlimit;
   unsigned short limit;
}PackInfo;

PackInfo init_pack(PackInfo p, unsigned short limit){
   p.rem = 1;
   p.pow = 9;
   p.excess = 0;
   p.maxcode = 257;
   p.currlimit = 512;
   p.limit = limit;
   return p;
}

PackInfo reset_pack(PackInfo p){
   p.rem = 1;
   p.pow = 9;
   p.maxcode= 257;
   p.currlimit = 512;
   return p;
}

PackInfo new_packet_size(PackInfo p){
   p.currlimit = p.currlimit * 2;
   p.pow = p.pow + 1;
   p.rem = p.pow - 8;
   return p;
}


TrieNode* innerlogic(TrieNode* prevnode, TrieNode* currnode, TrieNode *root, 
   FILE* output, int c, int *in_tree, PackInfo* p, unsigned short *curr,
   TrieNode* nul_next[], Code codarr[]){
   prevnode = currnode;
   currnode = get(currnode, c, in_tree, nul_next, codarr);
   if(p->maxcode -1 == p->limit + *in_tree){
      packbits_write(*curr,&(p->excess),&(p->rem), output, p->pow);
      soft_delete(root, root, root, nul_next, codarr);
      currnode = root;
      *p = reset_pack(*p);
      *curr = (currnode->code)[c];
      prevnode = currnode;
      return get(currnode, c, in_tree, nul_next, codarr);
   }
      
   else if(*in_tree == -1){
      currnode = insert(currnode,c, p->maxcode, root);
      p->maxcode = p->maxcode + 1;
      packbits_write(*curr, &(p->excess), &(p->rem), output, p->pow);
      *curr = (currnode->code)[c];
      prevnode = currnode;
      return get(currnode, c, in_tree, nul_next, codarr);
   }
   *curr = (prevnode->code)[c];
   return currnode;
   
}

void perm_delete(TrieNode* root, FILE* input, FILE* output){
   delete_trie(root, root);
   free(root);
   fclose(input);
   fclose(output);
}
   
void logic_runner(FILE* input, FILE* output, unsigned short limit){
   unsigned short curr = 0;
   PackInfo p;
   TrieNode* root = NULL , *currnode = NULL, *prevnode = NULL;
   int c = 0, in_tree = 0;
   TrieNode* nul_next[NUMBER_OF_SYMBOLS];
   Code newcode[NUMBER_OF_SYMBOLS];
   init_newcode(newcode);
   p = init_pack(p, limit);
   init_next(nul_next);
   root = init_trie(nul_next); 
   currnode = root;
   while((c= getc(input)) != EOF){
      
      if(p.maxcode == p.currlimit + 1) 
         p = new_packet_size(p);

      currnode = innerlogic(prevnode, currnode, root, output, c, &in_tree,
         &p, &curr, nul_next, newcode);   
   }
   if(p.maxcode == p.currlimit + 1) 
     * p = new_packet_size(p);
   
   packbits_write(curr,&(p.excess),&(p.rem),output,p.pow); 
   packbits_write(256, &(p.excess), &(p.rem), output, p.pow);
   trailwrite(&(p.excess), &(p.rem), output, p.pow);
   perm_delete(root, input, output);
}

void checkempty(FILE* input, FILE* output){
   int size = 0;
   fseek (input, 0, SEEK_END);
   size = ftell(input);

   if (size == 0) {
      fclose(input);
      fclose(output);
      exit(0);
   }
   rewind(input);
}

int main(int argc, char * argv[]){
   unsigned short limit = 0;
   char N = 12, filename[1024];
   FILE *inputptr = NULL, *outputptr = NULL; 
   if(argc < 2 || argc > 3)
      exit(exit_script());
   
   else if(argc == 2)
      strcpy(filename ,argv[1]);
   
   else if(setup_Rec(&N,filename, argv) == -1)
      exit(exit_script());
   
   if((inputptr = fopen(filename, "r")) == NULL){
      fprintf(stderr, "lzwCompress: ");
      perror(filename);
      exit(EXIT_FAILURE);
   }

   strcat(filename, ".lzw");

   if((outputptr = fopen(filename, "w")) == NULL){
      fprintf(stderr, "lzwCompress: ");
      perror(filename);
      exit(EXIT_FAILURE);
   }
   checkempty(inputptr, outputptr);

   fprintf(outputptr, "%c", N);
   limit = math_pow(2, N);
   logic_runner(inputptr, outputptr, limit);
   
   return 0;
}
