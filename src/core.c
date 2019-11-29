#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <hashmap.h>
#include <types.h>
#include <stack.h>

u4 get_type(u4 a_type, u4 b_type){
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
u4 multiply(struct stack * s, char ** p_string, int pc){
  if(size(s) < 2){
    printf("The stack is too small to multiply. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = get_type(a_type, b_type);
  push(s, CAST(a,a_type)*CAST(b,b_type), t);
  return 1;
}

/* ( n1 n2 -- n3 )
 * Divide n1 by n2, giving the single-cell quotient n3. An ambiguous condition exists if n2 is zero. */
u4 divide(struct stack * s, char ** p_string, int pc){
  if(size(s) < 2){
    printf("The stack is too small to divide. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = get_type(a_type, b_type);
  if(CAST(a,a_type) == 0){
    printf("Tried to dvide by 0. Exiting.\n");
    exit(0);
  }
  push(s, CAST(b,b_type)/CAST(a,a_type), t);
  return 1;
}

/* ( n1 | u1 n2 | u2 -- n3 | u3 )
 * Add n2 | u2 to n1 | u1, giving the sum n3 | u3. */
u4 add(struct stack * s, char ** p_string, int pc){
  if(size(s) < 2){
    printf("The stack is too small to add. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = get_type(a_type, b_type);
  push(s, CAST(a,a_type)+CAST(b,b_type), t);
  return 1;
}

/* ( n1 | u1 n2 | u2 -- n3 | u3 )
 * Subtract n2 | u2 from n1 | u1, giving the difference n3 | u3. */
u4 subtract(struct stack * s, char ** p_string, int pc){
  if(size(s) < 2){
    printf("The stack is too small to subtract. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = get_type(a_type, b_type);
  push(s, CAST(b,b_type)-CAST(a,a_type), t);
  return 1;
}

/* ( "ccc<quote>" -- )
 * Parse ccc delimited by " (double-quote). Display ccc. */
u4 print(struct stack * s, char ** p_string, int pc){
  int idx = pc;
  idx++;
  while(p_string[idx][strlen(p_string[idx]) - 1] != '"')
    printf("%s ", p_string[idx++]);
  p_string[idx][strlen(p_string[idx]) - 1] = '\0';
  printf("%s", p_string[idx++]);
  return idx - pc;
}

map_t construct_core_namespace(){
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
  return core_ns;
}