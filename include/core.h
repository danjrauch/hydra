#ifndef CORE_H_
#define CORE_H_

#pragma once

map_t construct_namespace();

/* : */
u4 def(struct stack * s, char ** p_string, int pc, map_t ns);
/* * */
u4 multiply(struct stack * s, char ** p_string, int pc, map_t ns);
/* / */
u4 divide(struct stack * s, char ** p_string, int pc, map_t ns);
/* + */
u4 add(struct stack * s, char ** p_string, int pc, map_t ns);
/* - */
u4 subtract(struct stack * s, char ** p_string, int pc, map_t ns);
/* ." */
u4 print(struct stack * s, char ** p_string, int pc, map_t ns);
/* 1+ */
u4 add_one(struct stack * s, char ** p_string, int pc, map_t ns);

#endif