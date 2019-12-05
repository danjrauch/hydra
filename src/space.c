#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <types.h>
#include <space.h>

// #define MEM_UNIT_SIZE

typedef struct mem_unit {
  value v;
  u4 status;
} mem_unit;

struct space {
  void * ptr;
  u8 size;
};

struct space * init_space(){
  struct space * s = (struct space *) malloc(sizeof(struct space));
  if(s == NULL){
    printf("Failed to initialize a space. Exiting.\n");
    exit(0);
  }
  s->ptr = malloc(sizeof(mem_unit));
  s->size = 1;
  mem_unit * mu = (mem_unit *) s->ptr;
  mu->status = 0;
  return s;
}

void * get_ptr(struct space * s){
  return s->ptr;
}

u8 get_size(struct space * s){
  return s->size;
}

void * space_store(struct space * s, value v, u8 offset, i4 use_offset){
  mem_unit * mu;
  if(s->ptr == NULL)
    return s->ptr;
  else if(use_offset > 0){
    if(offset + 1 > s->size){
      s->ptr = realloc(s->ptr, (offset+1) * sizeof(mem_unit));
      for(char * ptr = (char *) s->ptr + s->size * sizeof(mem_unit);
        ptr < (char *) s->ptr + (offset+1) * sizeof(mem_unit);
        ptr += sizeof(mem_unit)){
        mu = (mem_unit *) ptr;
        mu->status = mu->status | 1;
        s->size++;
      }
    }
    mu = (mem_unit *) ((char *) s->ptr + offset * sizeof(mem_unit));
    mu->v = v;
    mu->status = mu->status | 1;
    return (void *) mu;
  }else{
    for(char * ptr = (char *) s->ptr;
      ptr < (char *) s->ptr + s->size * sizeof(mem_unit);
      ptr += sizeof(mem_unit)){
      mu = (mem_unit *) ptr;
      if((mu->status & 1) == 0){
        mu->v = v;
        mu->status = mu->status | 1;
        return ptr;
      }
    }
    s->ptr = realloc(s->ptr, s->size * sizeof(mem_unit) + sizeof(mem_unit));
    mu = (mem_unit *) ((char *) s->ptr + s->size * sizeof(mem_unit));
    mu->v = v;
    mu->status = mu->status | 1;
    s->size++;
    return (void *) mu;
  }
  return NULL;
}

value space_retrieve(struct space * s, u8 offset){
  if(offset < 0)
    return (value) {-1, T_i4};
  mem_unit * mu = (mem_unit *) ((char *) s->ptr + offset * sizeof(mem_unit));
  return mu->v;
}