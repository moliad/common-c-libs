//------------------------------------------------
// file:    clibs-macros-bitwise.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2010-02-06
// version: 1.0.0
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: Macros which help with bit twiddling and flags management
//------------------------------------------------

#pragma once


// return a value with a single bit set to "ON"
//
// note that this uses 1-based bit numerals, so 1-64
//
// TODO : verify if we need to have the type specifier in left operand. 
//        if so, what happens if we use a 64 bit LL descriptor
#define bit(btNUm) ((1UL) << (btNUm - 1))




//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- BIT FLAGS MANAGEMENT
//
//-----------------------------------------------------------------------------------------------------------
#define CLEAR(valuE, flaG) ((valuE) &= ~ ( flaG ))
#define SET(valuE, flaG) ((valuE) |= (flaG))
#define CLEAR_FLAG(valuE, flaG) ((valuE) &= ~ ( flaG ))
#define KEEP_FLAGS(valuE, flaG) ((valuE) &= ( flaG ))
#define SET_FLAG(valuE, flaG) ((valuE) |= (flaG))
#define HAS_ALL_FLAGS(valuE, flagS)  (((valuE) & (flagS)) == (flagS))
#define HAS_ANY_FLAG(valuE, flagS)  (((valuE) & (flagS)) != 0)

// alternate spelling for HAS_ALL_FLAGS() easier to read
#define IS_FLAGGED(valuE, flagS) HAS_ALL_FLAGS(valuE, flagS)
#define NOT_FLAGGED(valuE, flagS)  (((valuE) & (flagS)) == 0)

