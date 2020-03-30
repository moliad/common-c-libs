//------------------------------------------------
// file:    clibs-src-macros.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2010-02-06
// version: 1.0.0
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: Core macros used by other basic includes to manage source code.
//------------------------------------------------

//                                                                         .
//-----------------------------------------------------------------------------------------------------------
//
//- SOURCE QUOTING MACROS
//
//-----------------------------------------------------------------------------------------------------------
#define STRINGIFY(s) XSTR__(s)
#define QUOTE(s) XSTR__(s)
#define XSTR__(s) #s

