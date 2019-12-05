#include <stdlib.h>
#include <stdio.h>
#include <types.h>
#include <stack.h>

#define LOW_4(x) (((x) << 32) >> 32)
#define HIGH_4(x) ((x) >> 32)

typedef struct cell {
  value val;
  struct cell * prev;
} cell;

struct stack {
  cell * top;
  u8 size;
};

/* Init a struct from the heap.
 * Returns: pointer to the stack struct */
struct stack * init_stack(){
  struct stack * s = (struct stack *) malloc(sizeof(struct stack));
  if(s == NULL){
    printf("Failed to initialize stack. Exiting.\n");
    exit(0);
  }
  s->size = 0;
  return s;
}

/* Get the size of s.
 * Returns: size of s */
u8 size(struct stack * s){
  return s->size;
}

/* Peek the type of primitive on top of s.
 * Returns: u4 type of primitive */
u4 peek_type(struct stack * s){
  return s->top->val.t;
}

/* Pop a single cell off s.
 * Returns: u8 of primitive */
u8 pop_4(struct stack * s){
  cell * c = s->top;
  u8 ret = c->val.v;
  s->top = s->top->prev;
  free(c);
  s->size--;
  return ret;
}

/* Pop a primitive off s.
 * Returns: u4 returns the type of popped primitive */
u4 pop(struct stack * s, void * cont){
  if(size(s) == 0){
    printf("The stack is empty. Pop failed. Exiting.\n");
    exit(0);
  }
  u4 type = peek_type(s);
  switch(type) {
    case T_u8 :
      *((u8 *) cont) = (u8) ((u8) pop_4(s) << 32 | pop_4(s));
      break;
    case T_i8 :
      *((i8 *) cont) = (i8) ((i8) pop_4(s) << 32 | pop_4(s));
      break;
    // case T_d8 :
    //   *((d8 *) cont) = (d8) ((u8) pop_4(s) << 32 | pop_4(s));
    //   break;
    case T_u4 :
      *((u4 *) cont) = (u4) pop_4(s);
      break;
    case T_i4 :
      *((i4 *) cont) = (i4) pop_4(s);
      // printf("POP_4: %uu %ds\n", *((i4 *) cont), CAST(*((i4 *) cont), T_i4));
      break;
    case T_f4 :
      *((f4 *) cont) = (f4) pop_4(s);
      break;
    default :
      printf("Error popping from stack. Exiting.\n");
      exit(0);
  }
  return type;
}

/* Push a value to s.
 * Returns: success: 0; failure: 1 */
u4 push_4(struct stack * s, u4 v, u4 t){
  cell * c = (cell *) malloc(sizeof(cell));
  if(c == NULL){
    printf("Failed to push a value on a stack. Exiting.\n");
    exit(0);
  }
  c->prev = s->top;
  c->val = (value) {v, t};
  // printf("PUSH_4: %uu %ds\n", v, CAST(v, t));
  s->top = c;
  s->size++;
  return 0;
}

/* Push a value to s in pieces given a type.
 * Returns: success: 0; failure: 1 */
u4 push(struct stack * s, u8 v, u4 type){
  if(type == T_u8 || type == T_i8 ||
     type == T_d8){
    push_4(s, LOW_4(v), type);
    push_4(s, HIGH_4(v), type);
  }else if(type == T_u4 || type == T_i4 ||
           type == T_f4){
    push_4(s, (u4) v, type);
  }else{
    printf("Error pushing to stack. Exiting.\n");
    exit(0);
  }
  return 0;
}