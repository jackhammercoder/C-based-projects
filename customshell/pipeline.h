#ifndef PIPELINE_H
#define PIPELINE_H


/* this function will store the pieces of the pipeline
 * into a char**. This will be fifo based on how strtok 
 * works, return the command count.
 */

int parsepipe(char** pieces, char buf[]);


/* helper function for parsepipe
 *  * determines is a token is valid
 *   */

int invalid(char * token);

/* this is the generic exit message for multiple errors
 * that occure
 */

int checkedges(char buf[], int* i);

int exitscript(const char * message);

int checkpieces(char** pieces, int num_cmds);

int invalidpiece(char * cmdpiece);

#endif

