#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hashmap.h>
#include <types.h>
#include <stack.h>
#include <core.h>

int interp_file(char * filename){
  map_t core_ns = construct_core_namespace();
  struct stack * d_stack = init_stack();
  char * buffer= NULL;
  long length;
  FILE * f = fopen(filename, "r");
  if(f){
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *) malloc(length);
    if(buffer)
      fread(buffer, 1, length, f);
    fclose(f);
  }
  // printf("%s\n", buffer);
  char * token;
  token = strtok(buffer, " ");
  while(token != NULL){
    int (*instr_func)();
    int result = hashmap_get(core_ns, token, (void *) &instr_func);
    if(result == MAP_MISSING)
      push(d_stack, atoi(token), T_i4);
    else if(result == MAP_OK)
      (*instr_func)(d_stack);
    token = strtok(NULL, " ");
  }
  // u8 a;
  // u4 a_type = pop(d_stack, &a);
  // printf("%d %u\n", a, a_type);

  free(d_stack);
  free(core_ns);
  return 0;
}