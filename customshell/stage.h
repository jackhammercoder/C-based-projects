#ifndef STAGE_H
#define STAGE_H

typedef struct{
   char inputname[1024];
   char outputname[1024];
   char * argv[12];
   int arg_num;
}Stage;

Stage init_stage();

Stage getstage(char** pipepieces, int num_cmds);

Stage fillStage(char * temp, Stage s);

void fill_tok_arr(char** tokens_arr, int *num_tokens, char * str);

#endif

