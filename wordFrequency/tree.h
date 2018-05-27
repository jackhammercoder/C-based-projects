#ifndef TREE_H
#define TREE_H
#include "getWord.h"

/* going to attempt to use a AVL self  balancing tree so an variable 
 * height is needed to indicate the 'height' of the node. must be int since can take negative values. 
*/

struct Node
{
   char *word;
   unsigned count;
   struct Node *left;
   struct Node *right;
   int height;
   unsigned len; 
};

/* this function will insert a particuliar word into a tree, and then also 
 * return the pointer to the root of our tree 
 * */
struct Node* insert(struct Node *addptr,char *word, unsigned len, unsigned *uni);

/* this function will intialize an instance of Node, 
 * that is, it will set is children to NULL and its height to zero
 */

struct Node* initNode(char *word, unsigned int len);

/*this function is a helper function for maintaing balance, it calculates the balannce
 * i.e. the differcent of the heights of the children of a node
 */

int getbalance(struct Node *nodeptr);

struct Node* rightRot(struct Node *node);

/* left rotation helper function, the same logic as right but now the rotation is the left. */

struct Node* leftRot(struct Node *node);

/* this function will upadate our heights for our tree, this is important 
 * so we can easily check balance variable to rebalance out tree if needed */

void newHeight(struct Node *node);

/* helper funtion for newHeight that calculates the max height of the subtrees */ 
int max(int a, int b);

/* this function dumps the contents of out tree into an array. This will
 * allow us to later sort the array by counts and return the top n counts
 * used by passing in a dynamically sized wordarray nad int = 0
 */

int treedump(struct Node *node, struct Node **wordarr, int i);

/* helper function for treedump that takes word* and counts from a node and put them into a
 *  * word Struct */

int compareNew(struct Node *node1, char *word, unsigned len);

unsigned minlen(struct Node *node1, unsigned len);

void deallocate(struct Node **node, unsigned uni);
struct Node* resize(struct Node *currnode, char * word, unsigned len,int balance);
#endif


