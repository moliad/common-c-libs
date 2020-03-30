//------------------------------------------------
// file:    clibs-selftest.c
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-03-08
// version: 1.0.0
// 
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: compiling this will proof that your compilation setup is ok.
//          any configuration, invalid compiler switch or other issue should
//          cause this code to fail miserably.
//------------------------------------------------

#include "clibs-env.h"

//---------------------------------------
// just testing the clib generic warning macro
//---------------------------------------
COMPILER_WARNING(Testing Clibs compiler warning)

