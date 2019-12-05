#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <hashmap.h>
#include <types.h>
#include <stack.h>
#include <space.h>

u4 new_type(u4 a_type, u4 b_type){
  u4 min_type = min(a_type, b_type);
  // if(min_type == T_f4 || min_type == T_d8)
  //   return min_type;
  if(a_type & 1 || b_type & 1){
    if((min_type & 1) == 0)
      return min_type + 1;
  }
  return min_type;
}

/* ( n1 | u1 n2 | u2 -- n3 | u3 )
 * Multiply n1 | u1 by n2 | u2 giving the product n3 | u3. */
u4 multiply(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to multiply. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = new_type(a_type, b_type);
  push(s, CAST(a,a_type)*CAST(b,b_type), t);
  return 1;
}

/* ( n1 n2 -- n3 )
 * Divide n1 by n2, giving the single-cell quotient n3. An ambiguous condition exists if n2 is zero. */
u4 divide(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to divide. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = new_type(a_type, b_type);
  if(CAST(a,a_type) == 0){
    printf("Tried to dvide by 0. Exiting.\n");
    exit(0);
  }
  push(s, CAST(b,b_type)/CAST(a,a_type), t);
  return 1;
}

/* ( n1 | u1 n2 | u2 -- n3 | u3 )
 * Add n2 | u2 to n1 | u1, giving the sum n3 | u3. */
u4 add(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to add. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = new_type(a_type, b_type);
  push(s, CAST(a,a_type)+CAST(b,b_type), t);
  return 1;
}

/* ( n1 | u1 n2 | u2 -- n3 | u3 )
 * Subtract n2 | u2 from n1 | u1, giving the difference n3 | u3. */
u4 subtract(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to subtract. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = new_type(a_type, b_type);
  push(s, CAST(b,b_type)-CAST(a,a_type), t);
  return 1;
}

/* ( "ccc<quote>" -- )
 * Parse ccc delimited by " (double-quote). Display ccc. */
u4 print(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  int idx = pc + 1;
  while(p_string[idx][strlen(p_string[idx]) - 1] != '"')
    printf("%s ", p_string[idx++]);
  p_string[idx][strlen(p_string[idx]) - 1] = '\0';
  printf("%s", p_string[idx++]);
  return idx - pc;
}

/* ( n1 | u1 -- n2 | u2 )
 * Add one (1) to n1 | u1 giving the sum n2 | u2. */
u4 add_one(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 1){
    printf("The stack is too small to add one. Exiting.\n");
    exit(0);
  }
  u8 a;
  u4 a_type = pop(s, &a);
  push(s, CAST(a,a_type)+1, a_type);
  return 1;
}

/* ( n1 | u1 -- n2 | u2 )
 * Subtract one (1) from n1 | u1 giving the difference n2 | u2. */
u4 subtract_one(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 1){
    printf("The stack is too small to subtract one. Exiting.\n");
    exit(0);
  }
  u8 a;
  u4 a_type = pop(s, &a);
  push(s, CAST(a,a_type)-1, a_type);
  return 1;
}

/* ( n1 n2 -- n3 )
 * n3 is the lesser of n1 and n2. */
u4 minimum(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to find a minimum. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  // printf("a: %lu b: %lu\n", a, b);
  // printf("MIN: a -> %uu %ds\n", a, CAST(a, a_type));
  // printf("MIN: b -> %uu %ds\n", b, CAST(b, b_type));
  // printf("%d\n", (i4) a < (i4) b);
  // printf("%d\n", CAST(-1, T_i4) == CAST(0, T_i4));
  // printf("%d\n", CAST(a, a_type) < CAST(b, b_type));
  if(a_type == T_i4 && b_type == T_i4){
    if((i4)CAST(a, a_type) < (i4)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_i8 && b_type == T_i8){
    if((i8)CAST(a, a_type) < (i8)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_u4 && b_type == T_u4){
    if((u4)CAST(a, a_type) < (u4)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_u8 && b_type == T_u8){
    if((u8)CAST(a, a_type) < (u8)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else{
    printf("The types need to match in order to find a minimum. Exiting.\n");
    exit(0);
  }
  return 1;
}

/* ( n1 n2 -- n3 )
 * n3 is the lesser of n1 and n2. */
u4 maximum(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to find a maximum. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  // printf("a: %lu b: %lu\n", a, b);
  // printf("MIN: a -> %uu %ds\n", a, CAST(a, a_type));
  // printf("MIN: b -> %uu %ds\n", b, CAST(b, b_type));
  // printf("%d\n", (i4) a < (i4) b);
  // printf("%d\n", CAST(-1, T_i4) == CAST(0, T_i4));
  // printf("%d\n", CAST(a, a_type) < CAST(b, b_type));
  if(a_type == T_i4 && b_type == T_i4){
    if((i4)CAST(a, a_type) > (i4)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_i8 && b_type == T_i8){
    if((i8)CAST(a, a_type) > (i8)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_u4 && b_type == T_u4){
    if((u4)CAST(a, a_type) > (u4)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else if(a_type == T_u8 && b_type == T_u8){
    if((u8)CAST(a, a_type) > (u8)CAST(b, b_type))
      push(s, CAST(a, a_type), a_type);
    else
      push(s, CAST(b, b_type), b_type);
  }else{
    printf("The types need to match in order to find a minimum. Exiting.\n");
    exit(0);
  }
  return 1;
}

/* ( C: "<spaces>name" -- colon-sys ) */
u4 def(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  int idx = pc + 1;
  char * name = strcat(p_string[idx], "_");
  char * definition = (char *) malloc(1000 * sizeof(char));
  while(strcmp(p_string[++idx], ";")){
    strcat(definition, p_string[idx]);
    strcat(definition, " ");
  }
  definition[strlen(definition) - 1] = '\0';
  // printf("putting %s=%s into ns\n", name, definition);
  hashmap_put(ns, name, (any_t) definition);
  idx++;
  return idx - pc;
}

/* ( x a-addr -- )
 * Store x at a-addr. */
u4 store(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns){
  if(size(s) < 2){
    printf("The stack is too small to store a value. Exiting.\n");
    exit(0);
  }
  u8 addr, x;
  u4 addr_type = pop(s, &addr);
  u4 x_type = pop(s, &x);
  if(addr_type == T_i4 || addr_type == T_u4)
    addr = (u8) ((u4) addr);
  else if(addr_type == T_i8)
    addr = (u8) addr;
  space_store(d_space, (value) {x, x_type}, addr, 1);
  value v = space_retrieve(d_space, addr);
  printf("%d : %s\n", CAST(v.v, v.t), TYPE_LABEL(v.t));
  return 1;
}

map_t construct_namespace(){
  map_t core_ns = hashmap_new();
  int error;
  error = hashmap_put(core_ns, "*", &multiply);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "/", &divide);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "+", &add);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "-", &subtract);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, ".\"", &print);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "1+", &add_one);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "1-", &subtract_one);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "MIN", &minimum);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "MAX", &maximum);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, ":", &def);
  assert(error == MAP_OK);
  error = hashmap_put(core_ns, "!", &store);
  assert(error == MAP_OK);
  return core_ns;
}