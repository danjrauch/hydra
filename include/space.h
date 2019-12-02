#ifndef SPACE_H_
#define SPACE_H_

#pragma once

#include <types.h>

struct space * init_space();
void * get_ptr(struct space * s);
u8 get_size(struct space * s);
void * space_store(struct space * s, value v, u8 offset, i4 use_offset);
value space_retrieve(struct space * s, u8 offset);

#endif