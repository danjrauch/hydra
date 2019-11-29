#ifndef CORE_H_
#define CORE_H_

#pragma once

map_t construct_core_namespace();

/* * */
u4 multiply(struct stack * s, char ** p_string, int pc);
/* / */
u4 divide(struct stack * s, char ** p_string, int pc);
/* + */
u4 add(struct stack * s, char ** p_string, int pc);
/* - */
u4 subtract(struct stack * s, char ** p_string, int pc);
/* ." */
u4 print(struct stack * s, char ** p_string, int pc);

#endif