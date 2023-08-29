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

#define SiAPI_FUNC(RTYPE) RTYPE
#define SiAPI_DATA(RTYPE) extern RTYPE

#include "macro.h"