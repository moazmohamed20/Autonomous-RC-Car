#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

#define FALSE 0
#define TRUE 1
#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed long int s32;

typedef float f32;
typedef double f64;
typedef long double f80;

typedef void (*func_ptr)(void);

#endif
