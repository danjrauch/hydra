#ifndef CORE_H_
#define CORE_H_

#pragma once

map_t construct_namespace();

/* : */
u4 def(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* * */
u4 multiply(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* / */
u4 divide(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* + */
u4 add(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* - */
u4 subtract(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* ." */
u4 print(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* 1+ */
u4 add_one(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* 1- */
u4 subtract_one(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* MIN */
u4 minimum(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* MAX */
u4 maximum(struct stack * s, struct stack * d_space, char ** p_string, int pc, map_t ns);
/* ! */
u4 store(struct stack * s, struct space * d_space, char ** p_string, int pc, map_t ns);

#endif