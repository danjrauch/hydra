#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hashmap.h>
#include <types.h>
#include <stack.h>
#include <core.h>

int interp_file(char * filename){
  int i;
  map_t core_ns = construct_core_namespace();
  struct stack * d_stack = init_stack();
  char * buffer = NULL;
  long length = 0, n_words = 0;
  FILE * f = fopen(filename, "r");
  if(f){
    int idx = 0;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *) malloc(length * sizeof(char));
    while(fscanf(f , "%c", &buffer[idx]) == 1)
      idx++;
    buffer[idx] = 0;
  }
  char * token;
  char ** p_string = (char **) malloc(length * sizeof(char *));
  int pc = 0;
  while((token = strtok_r(buffer, " ", &buffer))){
    p_string[pc] = (char *) malloc(strlen(token) * sizeof(char));
    strcpy(p_string[pc], token);
    pc++;
    n_words++;
  }
  for(pc = 0; pc < n_words; ++pc){
    int (*instr_func)();
    int result = hashmap_get(core_ns, p_string[pc], (void *) &instr_func);
    if(result == MAP_MISSING)
      push(d_stack, atoi(p_string[pc]), T_i4);
    else if(result == MAP_OK)
      pc += (*instr_func)(d_stack, p_string, pc) - 1;
  }
  u8 a;
  u4 a_type = pop(d_stack, &a);
  printf("%d %u\n", a, a_type);

  free(buffer);
  for(i = 0; i < n_words; ++i)
    free(p_string[i]);
  free(p_string);
  free(d_stack);
  free(core_ns);
  return 0;
}