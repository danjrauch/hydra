#ifndef STACK_H_
#define STACK_H_

#pragma once

struct stack * init_stack();
u4 peek_type(struct stack * s);
u4 peek(struct stack * s, void * cont);
u4 pop(struct stack * s, void * cont);
u4 push(struct stack * s, u8 val, u4 type);
u8 size(struct stack * s);

#endif