#include "tree.h"
#include <string.h>
#include <stdio.h>
#include "getWord.h"
#include <stdlib.h>

struct Node* insert(struct Node *currnode, char *word, unsigned len, 
   unsigned *uni){
   int balance = 0;
   if(currnode == NULL){
      *uni = *uni + 1;
      return initNode(word, len);
   }
   if (compareNew(currnode,word,len) == 0){
      (*currnode).count = (*currnode).count + 1;
      free(word);
      return currnode;
   }
   else if(compareNew(currnode,word,len) < 0)
      (*currnode).right = insert((*currnode).right, word, len, uni);
   else if(compareNew(currnode,word,len) > 0)
      (*currnode).left = insert((*currnode).left, word, len, uni);  
   
   newHeight(currnode);
   balance = getbalance(currnode);
   return resize(currnode,word,len,balance);   
}

struct Node* resize(struct Node *currnode, char * word, unsigned len,
   int balance){
   if(balance < -1){
      if(compareNew((*currnode).right,word,len) < 0)
         currnode = leftRot(currnode);
      else{
         (*currnode).right = rightRot((*currnode).right);
         currnode = leftRot(currnode);
      }
   }
   if(balance > 1){
      if(compareNew((*currnode).left,word,len) > 0)
         currnode = rightRot(currnode);
      else{
         (*currnode).left = leftRot((*currnode).left);
         currnode = rightRot(currnode);
      }
   }
   return currnode;
}

struct Node* initNode(char *word, unsigned len){
   struct Node *node = (struct Node *) malloc(sizeof(struct Node));
   if(node == NULL){
      perror("wf");
      exit(EXIT_FAILURE);
   } 
   (*node).word = word;
   (*node).height = 1;
   (*node).left = NULL;   
   (*node).right = NULL;
   (*node).count = 1;
   (*node).len = len;
   return node;
}

int getbalance(struct Node *nodeptr){
   int balance, leftH = 0, rightH = 0;
   if (nodeptr == NULL)
      return 0;
   if (nodeptr->right != NULL)
      rightH = nodeptr->right->height;
   if (nodeptr->left != NULL)
      leftH = nodeptr->left->height;
   balance = leftH - rightH;
   return balance; 
}

int compareNew(struct Node *node1, char *word, unsigned len){
   unsigned min = minlen(node1, len);
   int compare = memcmp((*node1).word,word,min);
   int diff = (*node1).len - len;
   if(compare == 0 && diff == 0)
      return 0;
   else if(compare == 0 && diff < 0)
      return -1;
   else if(compare == 0 && diff > 0)
      return 1;
   else if (compare > 0)
      return 1;
   return -1;  
}

unsigned minlen(struct Node *node1, unsigned len){
   if ((*node1).len < len){
      return (*node1).len;
   }
   return len;
}
  
struct Node* rightRot(struct Node *node){
   struct Node *proper = NULL;
   struct Node *temp = NULL;
   if (node == NULL)
      return node;
   proper = (*node).left;
   temp = (*proper).right;
   (*proper).right = node;
   (*node).left = temp;
   newHeight(node);
   newHeight(proper);
   return proper;
}

struct Node* leftRot(struct Node *node){
   struct Node *proper = NULL;
   struct Node *temp = NULL;
   if (node == NULL)
      return node;
   proper = (*node).right;
   temp = (*proper).left;
   (*proper).left = node;
   (*node).right = temp;
   newHeight(node);
   newHeight(proper);
   return proper;
}

void newHeight(struct Node *node){
   int rightH = 0 , leftH = 0;
   if (node->right != NULL)
      rightH = node->right->height;
   if (node->left != NULL)
      leftH = node->left->height; 
   node->height =  max(rightH, leftH) + 1;  
}

int max(int a, int b){
   if (a > b)
      return a;
   return b;
}

int treedump(struct Node *node, struct Node **arr, int i){
   if (node == NULL){
      return i;
   }
   arr[i] = node;
   i++;
   i = treedump((*node).left,arr,i);
   i = treedump((*node).right,arr,i);
   return i;
}

void deallocate(struct Node **node, unsigned uni){
   int i = 0;
   for(;i < uni; i++){
      free(node[i]->word);
      free(node[i]);
   }
   free(node);
}   
