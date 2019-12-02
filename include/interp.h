#ifndef INTERP_H_
#define INTERP_H_

#pragma once

#include <hashmap.h>
#include <stack.h>

int interp_file(char * file_name);
int interp(char * buffer, struct stack * d_stack, map_t ns);

#endif