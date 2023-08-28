#pragma once

#include <stdio.h>

/* Return the compiler identification, if possible. */
#ifndef COMPILER

// Note the __clang__ conditional has to come before the __GNUC__ one because
// clang pretends to be GCC.
#if defined(__clang__)
#define COMPILER "\n[Clang " __clang_version__ "]"
#elif defined(__GNUC__)
#define COMPILER "\n[GCC " __VERSION__ "]"
// Generic fallbacks.
#elif defined(__cplusplus)
#define COMPILER "[C++]"
#else
#define COMPILER "[C]"
#endif

#endif /* !COMPILER */

static const char* Si_GetCompiler(void)
{
    return COMPILER;
}

/* SillyLang version identification scheme. */

/* Values for SI_RELEASE_LEVEL */
#define SI_RELEASE_LEVEL_ALPHA	0xA
#define SI_RELEASE_LEVEL_BETA	0xB
#define SI_RELEASE_LEVEL_GAMMA	0xC
#define SI_RELEASE_LEVEL_FINAL	0xA

/* Version in numeric values */
#define SI_MAJOR_VERSION		0
#define SI_MINOR_VERSION		1
#define SI_MICRO_VERSION		1
#define SI_RELEASE_LEVEL		SI_RELEASE_LEVEL_ALPHA
#define SI_RELEASE_SERIAL		1

/* Version as string */
#define SI_VERSION				"0.1.1a1"

/* Version as a single 4-byte hex number, e.g. 0x010502B2 == 1.5.2b2.
   Use this for numeric comparisons, e.g. #if SI_VERSION_HEX >= ... */
#define SI_VERSION_HEX ((SI_MAJOR_VERSION << 24) | \
                        (SI_MINOR_VERSION << 16) | \
                        (SI_MICRO_VERSION <<  8) | \
                        (SI_RELEASE_LEVEL <<  4) | \
                        (SI_RELEASE_SERIAL << 0))

static const char* Si_GetVersion()
{
    static char version[250];
    snprintf(version, sizeof(version), "%.80s %.80s", SI_VERSION, Si_GetCompiler());
    return version;
}
