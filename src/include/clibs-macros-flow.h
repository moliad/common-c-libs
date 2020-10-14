//------------------------------------------------
// file:    clibs-macros-flow.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-10-14
// version: 1.0.0
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: Macros which extend the syntax of the C language with new statements.
//------------------------------------------------


#pragma once

 
#define unless(conditioN) if ((conditioN) == false)

#define repeat(cTr, lOOps) for(cTr=0 ; cTr < (lOOps) ; cTr++)

#define foreach(vaR, arraY, cTr, lOOps) for(cTr=0 ; cTr < (lOOps) ; vaR = arraY[cTr++])