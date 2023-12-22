#ifndef ULTRA64_ULTRATYPES_H
#define ULTRA64_ULTRATYPES_H

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

// clang-format off
typedef signed char            s8;     /* signed 8-bit */
typedef unsigned char          u8;     /* unsigned 8-bit */
typedef signed short int       s16;    /* signed 16-bit */
typedef unsigned short int     u16;    /* unsigned 16-bit */
typedef signed int             s32;    /* signed 32-bit */
typedef unsigned int           u32;    /* unsigned 32-bit */
typedef signed long long int   s64;    /* signed 64-bit */
typedef unsigned long long int u64;    /* unsigned 64-bit */
typedef u32                    size_t; /**/

typedef volatile u8            vu8;    /* unsigned 8-bit */
typedef volatile u16           vu16;   /* unsigned 16-bit */
typedef volatile u32           vu32;   /* unsigned 32-bit */
typedef volatile u64           vu64;   /* unsigned 64-bit */
typedef volatile s8            vs8;    /* signed 8-bit */
typedef volatile s16           vs16;   /* signed 16-bit */
typedef volatile s32           vs32;   /* signed 32-bit */
typedef volatile s64           vs64;   /* signed 64-bit */

typedef float                  f32;    /* single precision floating point */
typedef double                 f64;    /* double precision floating point */
// clang-format on

#endif // _LANGUAGE_C

#ifndef NULL
#define NULL (void*)0
#endif

// Leftover strings in the ROM suggest the usage of "NPTR" instead of "NULL"
#ifndef NPTR
#define NPTR (void*)0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef float MtxF[4][4];
typedef float mf[4][4];

#endif // ULTRA64_ULTRATYPES_H
