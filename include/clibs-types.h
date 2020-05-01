//------------------------------------------------
// file:    clib-types.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-03-21
// version: 1.0.1
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: stores simple and uniform typedefs
//------------------------------------------------

#pragma once

#include "stdint.h"
#include "stdbool.h" // note we standardize (force) the usage of C99 bool in projects related to clibs


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- INTEGER TYPES
//
//-----------------------------------------------------------------------------------------------------------
typedef int64_t			i64;
typedef uint64_t		u64;
typedef int32_t 		i32;
typedef uint32_t		u32;
typedef int16_t			i16;
typedef uint16_t		u16;
typedef char			i8;
typedef unsigned char	u8;

typedef text			char *;
typedef byte			u8
typedef codepoint		char *; // in utf8 


