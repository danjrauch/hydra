#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
u4 mult(struct stack * s){
  if(size(s) < 2){
    printf("The stack is too small to multiply. Exiting.\n");
    exit(0);
  }
  u8 a, b;
  u4 a_type = pop(s, &a);
  u4 b_type = pop(s, &b);
  u4 t = get_type(a_type, b_type);
  push(s, CAST(a,a_type)*CAST(b,b_type), t);
  return 0;
}

/* TODO build namespace dictionary */
map_t construct_core_namespace(){
  map_t core_ns = hashmap_new();
  int error;
  error = hashmap_put(core_ns, "*", &mult);
  assert(error == MAP_OK);
  return core_ns;
}