#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <hashmap.h>
#include <types.h>
#include <stack.h>
#include <space.h>
#include <core.h>
#include <limits.h>

void to_bin(u8 n){
  char s[64];
  int idx = 63;
  while(n){
    if(n & 1)
      s[idx--] = '1';
    else
      s[idx--] = '0';
    n >>= 1;
  }
}

int interp(char * buffer, struct stack * d_stack, struct space * d_space, map_t ns){
  int i, pc = 0, n_words = 0;
  char * token;
  char ** p_string = (char **) malloc(strlen(buffer) * sizeof(char *));
  while((token = strtok_r(buffer, " ", &buffer))){
    p_string[pc] = (char *) malloc(strlen(token) * sizeof(char));
    strcpy(p_string[pc], token);
    pc++;
    n_words++;
  }
  for(pc = 0; pc < n_words; ++pc){
    // printf("INST: %s\n", p_string[pc]);
    int (*instr_func)();
    int result = hashmap_get(ns, p_string[pc], (any_t) &instr_func);
    if(result == MAP_OK){
      pc += (*instr_func)(d_stack, d_space, p_string, pc, ns) - 1;
    }else{
      char * definition;
      result = hashmap_get(ns, strcat(p_string[pc], "_"), (any_t) &definition);
      if(result == MAP_OK)
        interp(definition, d_stack, d_space, ns);
      else{
        if(atol(p_string[pc]) > INT_MAX || atol(p_string[pc]) < INT_MIN)
          push(d_stack, atol(p_string[pc]), T_i8);
        else
          push(d_stack, atoi(p_string[pc]), T_i4);
      }
    }
  }

  free(buffer);
  for(i = 0; i < n_words; ++i)
    free(p_string[i]);
  free(p_string);
  return 0;
}

int interp_file(char * filename){
  map_t ns = construct_namespace();
  struct stack * d_stack = init_stack();
  struct space * d_space = init_space();
  // space_store(d_space, (value) {-5, T_i4}, 0, 2);
  // value v = space_retrieve(d_space, 0);
  // printf("%d : %s\n", CAST(v.v, v.t), TYPE_LABEL(v.t));
  char * buffer = NULL;
  long length = 0;
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
  interp(buffer, d_stack, d_space, ns);
  u8 a;
  u4 a_type = pop(d_stack, &a);
  printf("FINAL RESULT: %d of type %s\n", CAST(a, a_type), TYPE_LABEL(a_type));
  free(d_stack);
  free(d_space);
  free(ns);
  return 0;
}