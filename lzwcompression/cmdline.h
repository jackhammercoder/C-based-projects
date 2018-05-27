#ifndef CMDLINE_H
#define CMDLINE_H

/* will print the error message to stderr
* and return EXIT_FAILURE 
*/

int exit_script();

/* will set up the recylce code and the filename we will 
* be compressing.
* returns 1 if successful or -1 if unsuccessful
*/

int setup_Rec(char* N, char filename[], char* argv[]);

int scanin(char *N, char *currarg);

#endif 
