#ifndef INTERP_H_
#define INTERP_H_

#pragma once

#include <hashmap.h>
#include <stack.h>
#include <space.h>

int interp_file(char * file_name);
int interp(char * buffer, struct stack * d_stack, struct space * d_space, map_t ns);

#endif