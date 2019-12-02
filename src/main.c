#include <stdlib.h>
#include <stdio.h>
#include <types.h>
// #include <stack.h>
// #include <core.h>
#include <interp.h>
#include <hashmap.h>
#include <assert.h>

int main(int argc, char **argv){
  if(argc == 2)
    interp_file(argv[1]);
  else if(argc == 3)
    interp_file("p.forth");
  return 0;
}