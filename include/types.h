#pragma once

/* Linux x64 */
typedef long           i8;
typedef int            i4;
typedef short          i2;
typedef unsigned long  u8;
typedef unsigned int   u4;
typedef unsigned short u2;
typedef unsigned char  u1;
typedef float          f4;
typedef double         d8;

// typedef unsigned char Bool;
// #define bool Bool

// #define false 0
// #define true 1

#define T_f4 1
#define T_d8 3
#define T_u4 4
#define T_i4 5
#define T_u8 6
#define T_i8 7

#define T_b 10
#define T_c1 12
#define T_us 14

typedef struct value {
  u4 v;
  int t;
} value;

#define CAST(v, t) \
    ( t==T_u4 ? (u4) v \
    : t==T_u8 ? (u8) v \
    : t==T_i4 ? (i4) v \
    : t==T_i8 ? (i8) v \
    : 0 )

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })