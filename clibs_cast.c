//------------------------------------------------
// file:    clibs_cast.c
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-20
// version: 1.0.1
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: datatype conversion
//------------------------------------------------

//#define VERBOSE
#include "vprint.h"
#include "clibs_cast.h"

//--------------------------
//-     i32_to_charptr()
//--------------------------
// purpose:  Convert given 32 bit signed int into char *
//
// inputs:
//
// returns: Number of characters written to buffer
// 			0 if not enough space
//
// notes:
//
// to do:
//
// tests:
//--------------------------
int i32_to_charptr(int value, char *buffer, int len){
	int val=0;
	int count=0;
	int i=0;
	int remainder=0;

	vin("i32_to_charptr()");
	//----
	// make sure inputs are valid
	if (
		   buffer == NULL
		|| len < 1
	){
		vprint("ERROR!! : Invalid buffer or len given");
		vout;
		return 0;
	}

	//----
	// count bytes
	vin("counting bytes");
	val = value;
	do {
		vnum(val);
		remainder = val % 10;
		vnum(remainder);
		val /= 10;
		++count;
		vprint("---");
	}while(
		val != 0
	);
	vnum(val);
	vnum(count);
	vout;

	//----
	// make buffer is large enough
	if (count > len){
		vprint("ERROR! : buffer size too small for value %i", value );
		vout;
		return 0;
	}

	//----
	// do the conversion
	vin("dumping to buffer");
	val=value;
	do {
		vnum(val);
		remainder = val % 10;
		vnum(remainder);
		++i;
		vnum(count - i);
		buffer[count - i] = 48 + remainder ;
		val /= 10;
		vprint("---");
	}while(
		val != 0
	);
	vout;
	vout;
	return count;
}


