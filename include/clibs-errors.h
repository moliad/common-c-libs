//------------------------------------------------
// file:    clibs-errors.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-26
// version: 1.0.0
//
// license: APACHE v2.0 
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: labeled error numbers for all aspects of the clib project.
//
// notes:   - make sure to follow the line numbers of the .c file.
//------------------------------------------------
#pragma once

//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- ERROR NUMBERS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//-     clibs_errors
//
// its defined extern, so it will not actually be defined, you MUST add and compile the .c file
// within your project for the actual string data to be part of your build.
//
// having the list of error numbers allows you to store the data only once and refer to it in all other 
// parts of your project.
//--------------------------
extern char *clibs_errors[];






//--------------------------
// this MUST be at line 40
//--------------------------

//--------------------------
//- clibs_errors:
//
// the offsets for all clib errors from the clibs_errors array
// all line numbers should be exactly the same for both files, in order to simplify detection of error and label mis-alignment.
//--------------------------
enum clibs_errors_enum  {
	ERR_CLIB_SUCCESS=0, // not an error, all is good
	ERR_CLIB_UNSPECIFIED=1,  // can be used as an equivalent for TRUE in conditionals
	
	// DATA CASTING ERRORS 
	ERR_CLIB_CAST_EMPTY_STRING,
	ERR_CLIB_CAST_INVALID_SRC_VALUE,
	ERR_CLIB_CAST_INCOMPATIBLE_DESTINATION_TYPE,
};

//-     SUCCESS
// note that this may be defined in other projets (usually also at 0). if there is discrepancy,
// you can undefine the and re-define value around this header file in the code using it.
#define SUCCESS ERR_CLIB_SUCCESS;

