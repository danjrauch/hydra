#include <stdlib.h>
#include <stdio.h>
#include <types.h>
// #include <stack.h>
// #include <core.h>
#include <interp.h>
#include <hashmap.h>
#include <assert.h>

int main(int argc, char **argv){
  // map_t mmap = hashmap_new();
  // char * val = (char *) malloc(4 * sizeof(char));
  // val = "rats on a hill";
  // printf("%s\n", val);
  // int error = hashmap_put(mmap, "hi", val);
  // assert(error == MAP_OK);
  // error = hashmap_get(mmap, "hi", (void *) &val);
  // assert(error == MAP_OK);
  // printf("%s\n", val);
  // hashmap_free(mmap);
  if(argc == 2)
    interp_file(argv[1]);
  else if(argc == 3)
    interp_file("p.forth");
  // printf("before\n");
  // print_bin(-8);
  // push(d_stack, -1, T_i4);
  // push(d_stack, -2, T_i4);
  // push(d_stack, -3, T_i4);
  // push(d_stack, 30, T_u8);
  // push(d_stack, -80, T_i8);
  // push(d_stack, 1, T_u4);
  // mult(d_stack);
  // mult(d_stack);
  // mult(d_stack);
  // u8 a;
  // u4 a_type = pop(d_stack, &a);
  // printf("%d %u\n", CAST(a,a_type), a_type);
  return 0;
}