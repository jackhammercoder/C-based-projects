#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

/* this will intialize the first 255 ascii characters and 
 * return a pointer to the head of the 
 * of the Trie structure.
 */

TrieNode* init_trie(TrieNode* nul_next[]){
   TrieNode* t = NULL;
   t = (TrieNode*) malloc(sizeof(TrieNode));
   init_code(t->code);
   memcpy(t->next, nul_next, sizeof t->next);
   return t;
}

/* this is a helper function for intializing the trie structure
 * it will take in the code array and intiatlize each index to the values
 * 0 - 255
 */

void init_code(Code code[]){
   unsigned short i = 0;
   for(; i < NUMBER_OF_SYMBOLS; i++){
      code[i] = i;
   }
}

void init_next(TrieNode * next[]){
   int i = 0;
   for(; i < NUMBER_OF_SYMBOLS; i++){
      next[i] = NULL;
   }
}

/* same idea as above but this is for a node that is not the 
 * root of the trie
 */

void init_newcode(Code code[]){
   unsigned short i = 0;
   for(; i < NUMBER_OF_SYMBOLS; i++){
      code[i] = 256;
   }
}

/* this adds a new string to the dictionary
 * then returns a pointer to the root of the tree
 * this is only called if get() returns -1; 
 */

TrieNode* insert(TrieNode* curr, int c, unsigned short maxcode, 
   TrieNode* root){
   (curr->code)[c] = maxcode;
   return root;
}

/* this a helper funciton to intialize a new 'node' for the tree
 * a new node is created when the index of a next array is null, 
 * then we make a new one.
 * it will return a pointer to the newly created node
 */

TrieNode* createNode(TrieNode* nul_next[], Code codarr[]){
   TrieNode* t = NULL;
   t = (TrieNode*) malloc(sizeof(TrieNode));
   memcpy(t->code, codarr, sizeof t->code);
   memcpy(t->next, nul_next, sizeof t->next); 
   return t;
}

/* this function will return the currnode, basically if you've 
 * already added AA and need to add AAB it will return the node 
 * for A_ and set the in_tree pointer to -1
 * which indicates that it needs to be inserted
 * if it is already in the tree it is done. i.e.
 * in_tree will be set to 1 and that node will be returned
 */

TrieNode* get(TrieNode* curr, int c, int* in_tree, TrieNode* nul_next[],
   Code codarr[]){
   TrieNode* next = NULL;
   next = (curr->next)[c];
   if (next == NULL){
      if((curr->code)[c] != 256){
         *in_tree = 1;
         (curr->next)[c] = createNode(nul_next, codarr);
         return (curr->next)[c];
      }
      *in_tree = -1;
      return curr;
   }
   if((curr->code)[c] != 256){
      *in_tree = 1;
      return next;
   }
   *in_tree = -1;
   return curr;
   
}

void delete_trie(TrieNode* curr, TrieNode* root){
   int i = 0;
   for(; i < NUMBER_OF_SYMBOLS; i++){
      if((curr->next)[i] != NULL){
         delete_trie((curr->next)[i], root);
         free(curr->next[i]);
      }
   }
}

void soft_delete(TrieNode* curr, TrieNode* root, TrieNode* prev,
   TrieNode* nul_next[], Code codarr[]){
   int i = 0;
   for(; i < NUMBER_OF_SYMBOLS; i++){
      if((curr->next)[i] != NULL)
         soft_delete((curr->next)[i], root, curr, nul_next, codarr);
   }
   if(prev != root){
      free(curr);
   }
   else if(curr != root){
      memcpy(curr->code, codarr, sizeof curr->code);
      memcpy(curr->next, nul_next, sizeof curr->next);
   }
}
