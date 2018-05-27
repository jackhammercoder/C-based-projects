#ifndef TRIE_H
#define TRIE_H

#define NUMBER_OF_SYMBOLS 256


typedef unsigned short Code;

typedef struct trieNode
{
   Code code[NUMBER_OF_SYMBOLS];
   struct trieNode *next[NUMBER_OF_SYMBOLS];
} TrieNode;

/* this will intialize the first 255 ascii characters and return a pointer to the head of the 
* of the Trie structure.
*/

TrieNode* init_trie(TrieNode* nul_next[]);

/* this is a helper function for intializing the trie structure
* it will take in the code array and intiatlize each index to the values
* 0 - 255
*/

void init_code(Code code[]);

void init_newcode(Code code[]);

/* this adds a new string to the dictionary
* then returns a pointer to the root of the tree 
*/

TrieNode* insert(TrieNode* curr, int c, unsigned short maxcode, TrieNode* root);

/* this a helper funciton to intialize a new 'node' for the tree
* a new node is created when the index of a next array is null, 
* then we make a new one.
* it will return a pointer to the newly created node
*/

TrieNode* createNode(TrieNode* nul_next[], Code codarr[]);

/* this function will get a particular code for a 
* string, if it can't be found it will return -1
*/

TrieNode* get(TrieNode* curr, int c, int* in_tree, TrieNode* nul_next[],
   Code codarr[]);

void init_next(TrieNode * next[]);

void delete_trie(TrieNode* curr, TrieNode* root);

void soft_delete(TrieNode* curr, TrieNode* root, TrieNode* prev,
   TrieNode* nul_next[], Code codarr[]);

#endif 
