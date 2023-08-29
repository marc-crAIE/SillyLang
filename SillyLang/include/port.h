#pragma once

#include <assert.h>
#include <memory>
#include <string>
#include <iostream>

#include "config.h"

#ifdef MS_WINDOWS

typedef int8_t    Si_int8_t;
typedef int16_t   Si_int16_t;
typedef int32_t   Si_int32_t;
typedef int64_t   Si_int64_t;

typedef uint8_t   Si_uint8_t;
typedef uint16_t  Si_uint16_t;
typedef uint32_t  Si_uint32_t;
typedef uint64_t  Si_uint64_t;

#else

typedef __int8_t    Cr_int8_t;
typedef __int16_t   Cr_int16_t;
typedef __int32_t   Cr_int32_t;
typedef __int64_t   Cr_int64_t;

typedef __uint8_t   Cr_uint8_t;
typedef __uint16_t  Cr_uint16_t;
typedef __uint32_t  Cr_uint32_t;
typedef __uint64_t  Cr_uint64_t;

#endif

typedef float       Si_float_t;
typedef double      Si_double_t;

typedef std::string Si_string_t;

typedef intptr_t	Si_intptr_t;
typedef Si_intptr_t Si_size_t;
typedef Si_size_t	Si_hash_t;

// Largest possible value of size_t.
#define SI_SIZE_MAX SIZE_MAX

// Largest positive value of type Cr_size_t.
#define SI_SIZE_T_MAX ((Si_size_t)(((size_t)-1)>>1))
// Smallest negative value of type Cr_size_t.
#define SI_SIZE_T_MIN (-SI_SIZE_T_MAX-1)

#define SiAPI_FUNC(RTYPE) RTYPE
#define SiAPI_DATA(RTYPE) extern RTYPE

#include "macro.h"