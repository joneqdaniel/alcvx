#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdalign.h>
#include <sys/param.h>
#include <stdarg.h>
#include <string.h>
#include "macros.h"

#define vec_ext(T,N) typeof(T __attribute__((vector_size(sizeof(T) * N))))
#define vec(T,N) typeof(T[N])

#undef countof
#define countof(a) (sizeof((a))/sizeof((a)[0]))
#define isarray(arg) __builtin_choose_expr(__builtin_types_compatible_p(typeof(arg[0]) [], typeof(arg)), true, false)
#define countargs(...) (0 __VA_OPT__(+sizeof((typeof(__VA_ARGS__)[]){__VA_ARGS__})/sizeof(__VA_ARGS__)))
#define emptyargs(...) (true __VA_OPT__(-1))

#define BITOP_RUP01__(x) (             (x) | (             (x) >>  1))
#define BITOP_RUP02__(x) (BITOP_RUP01__(x) | (BITOP_RUP01__(x) >>  2))
#define BITOP_RUP04__(x) (BITOP_RUP02__(x) | (BITOP_RUP02__(x) >>  4))
#define BITOP_RUP08__(x) (BITOP_RUP04__(x) | (BITOP_RUP04__(x) >>  8))
#define BITOP_RUP16__(x) (BITOP_RUP08__(x) | (BITOP_RUP08__(x) >> 16))

#define BIT_CEIL(x) (BITOP_RUP16__(((uint32_t)(x)) - 1) + 1)

#define ALCVX(src,n) (*(vec(typeof(src[0]),n)*)src)

#define sum(a,n,i) \
({ \
typeof((a)[0]) dst = i; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t j = 0; j < MIN(countargs(a),n); j++) \
	dst += (a)[j]; \
dst; \
})

#define dot(a,b,n,i) \
({ \
typeof((a)[0]) dst = i; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t j = 0; j < MIN(MIN(countargs(a),countargs(b)),n); j++) \
	dst += (a)[j] * (b)[j]; \
dst; \
})


#define minor(x,y,...) ({ \
vec(typeof(__VA_ARGS__), countargs(__VA_ARGS__)-1) dst[countargs(__VA_ARGS__)-1]; \
for(size_t i = 0; i < countargs(__VA_ARGS__)-1; i++) \
	for(size_t j = 0; j < countargs(__VA_ARGS__)-1; j++) \
		dst[i][j] = (i <  x && j <  y) ? (vec(typeof(__VA_ARGS__),countargs(__VA_ARGS__))[countargs(__VA_ARGS__)]){__VA_ARGS__}[i  ][j  ] : \
 	                    (i >= x && j <  y) ? (vec(typeof(__VA_ARGS__),countargs(__VA_ARGS__))[countargs(__VA_ARGS__)]){__VA_ARGS__}[i+1][j  ] : \
	                    (i <  x && j >= y) ? (vec(typeof(__VA_ARGS__),countargs(__VA_ARGS__))[countargs(__VA_ARGS__)]){__VA_ARGS__}[i  ][j+1] : \
		                                 COUNTO(vec(typeof(__VA_ARGS__),countargs(__VA_ARGS__))[countargs(__VA_ARGS__)]){__VA_ARGS__}[i+1][j+1]; \
dst; })

#define sum3(a) sum(a,3,0)
#define sum4(a) sum(a,4,0)
#define dot3(a,b) dot(a,b,3,0)
#define dot4(a,b) dot(a,b,4,0)

#define perm(a,...) { __VA_OPT__(EXPAND(perm_helper(a,__VA_ARGS__))) }
#define perm_helper(a,i,...) (a)[i], __VA_OPT__(perm_again PARENS (a,__VA_ARGS__))
#define perm_again() perm_helper
#define perm3(a,x,y,z) (vec(typeof((a)[0]),3))perm(a,x,y,z)
#define perm4(a,x,y,z,w) (vec(typeof((a)[0]),4))perm(a,x,y,z,w)

#define cross3(a,b) \
  perm3(a,1,2,0) * perm3(b,2,0,1) \
- perm3(a,2,1,0) * perm3(b,1,2,0)
/*
#define cross4(a,b,c) (vec(typeof((a)[0]),4))\
{ det(perm3(a,1,2,3), perm3(b,1,2,3), perm3(c,1,2,3)), \
 -det(perm3(a,0,2,3), perm3(b,0,2,3), perm3(c,0,2,3)), \
  det(perm3(a,0,1,3), perm3(b,0,1,3), perm3(c,0,1,3)), \
 -det(perm3(a,0,1,2), perm3(b,0,1,2), perm3(c,0,1,2)) }
*/

/* standard scalar types */
typedef float    f32;
typedef double   f64;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef  int64_t i64;
typedef  int32_t i32;
typedef  int16_t i16;
typedef  int8_t  i8;

typedef  int64_t s64;
typedef  int32_t s32;
typedef  int16_t s16;
typedef  int8_t  s8;

typedef  char     c8;
typedef  bool     b8;

typedef enum be32 : u32
{
	ALCVX_TRUE  = (const u32) true,
	ALCVX_FALSE = (const u32)!true,
} be32;

typedef  uintptr_t uptr;
typedef   intptr_t iptr;
typedef     size_t usz;
typedef    ssize_t ssz;

/* quake vector types */
typedef float          vecf_t;
typedef double         vecd_t;
typedef vecf_t         vec_t;

typedef vec_t          vec2_t[2];
typedef vec_t          vec3_t[3];
typedef vec_t          vec4_t[4];
typedef vec_t          vec5_t[5];
typedef vec_t          vec6_t[6];
typedef vec_t          vec7_t[7];
typedef vec_t          vec8_t[8];
typedef vec_t          vec9_t[9];
typedef vec_t          vec10_t[10];
typedef vec_t          vec11_t[11];
typedef vec_t          vec12_t[12];
typedef vec_t          vec13_t[13];
typedef vec_t          vec14_t[14];
typedef vec_t          vec15_t[15];
typedef vec_t          vec16_t[16];

typedef vec(float,2)  avec2_t;
typedef vec(float,3)  avec3_t;
typedef vec(float,4)  avec4_t;
typedef vec(float,5)  avec5_t;
typedef vec(float,6)  avec6_t;
typedef vec(float,7)  avec7_t;
typedef vec(float,8)  avec8_t;
typedef vec(float,9)  avec9_t;
typedef vec(float,10) avec10_t;
typedef vec(float,11) avec11_t;
typedef vec(float,12) avec12_t;
typedef vec(float,13) avec13_t;
typedef vec(float,14) avec14_t;
typedef vec(float,15) avec15_t;
typedef vec(float,16) avec16_t;

typedef vecd_t          vec2d_t[2];
typedef vecd_t          vec3d_t[3];
typedef vecd_t          vec4d_t[4];
typedef vecd_t          vec5d_t[5];
typedef vecd_t          vec6d_t[6];
typedef vecd_t          vec7d_t[7];
typedef vecd_t          vec8d_t[8];
typedef vecd_t          vec9d_t[9];
typedef vecd_t          vec10d_t[10];
typedef vecd_t          vec11d_t[11];
typedef vecd_t          vec12d_t[12];
typedef vecd_t          vec13d_t[13];
typedef vecd_t          vec14d_t[14];
typedef vecd_t          vec15d_t[15];
typedef vecd_t          vec16d_t[16];
