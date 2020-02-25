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

#define VERBOSE
#include "vprint.h"
#include "clibs_cast.h"
#include <math.h>

//--------------------------
//-     i64_to_charptr()
//--------------------------
// purpose:  Convert given 32 bit signed int into char *
//
// inputs:
//
// returns: Number of characters written to buffer
// 			0 if not enough space
//
// notes:	DOES NOT NULL TERMINATE STRING
//
// to do:
//
// tests:
//--------------------------
int i64_to_charptr(long long int value, char *buffer, int len){
	int val=0;
	int count=0;
	int i=0;
	int remainder=0;

	vin("i64_to_charptr()");
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
		//vnum(val);
		remainder = val % 10;
		//vnum(remainder);
		val /= 10;
		++count;
		//vprint("---");
	}while(
		val != 0
	);
	//vnum(val);
	vnum(count);
	vout;

	//----
	// make buffer is large enough
	if (count > len){
		vprint("ERROR! : buffer size too small for value %I64d ", value );
		vout;
		return 0;
	}

	//----
	// do the conversion
	vin("dumping to buffer");
	val=value;
	do {
		//vnum(val);
		remainder = val % 10;
		vnum(remainder);
		++i;
		//vnum(count - i);
		buffer[count - i] = 48 + remainder ;
		val /= 10;
		//vprint("---");
	}while(
		val != 0
	);
	vout;
	vout;
	return count;
}



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
// notes:	DOES NOT NULL TERMINATE STRING
//
// to do:
//
// tests:
//--------------------------
int i32_to_charptr(int value, char *buffer, int len){
	int count=0;
	// C will automatically promote the 32 bit value to its 64 bit equivalent, 
	// so we can reuse the same 64 bit function for both values.
	count = i64_to_charptr(value, buffer, len);
	return count;
}



//--------------------------
//-     double_to_charptr()
//--------------------------
// purpose:  convert a double precisiong floating point number to a char.
//
// inputs:   
//
// returns:  
//
// notes:    NEVER USES scientific notation
//       	 DOES NOT NULL TERMINATE STRING
//           we do not ROUND(), we FLOOR() the remainer by casting it to integer.
//
// to do:    
//
// tests:    
//--------------------------
int double_to_charptr(double value, int precision, char *buffer, int len ){
	long long int integer = 0;
	double remainder = 0.0;
	int sublen=0;
	int count=0;
	
	
	
	vin("double_to_charptr()");
	vprint("%.20f", value);

	integer = value;              // extract the integer part of the value
	remainder = value - integer;  // extract the floating point remainder
	
	sublen = i64_to_charptr(integer, buffer, len);
	count = sublen;
	
	if (remainder != 0){
		// make sure the given buffer was able to convert at least integer before continuing.
		if (sublen){
			if (sublen < len){
				// add floating point dot '.'
				vprint("adding dot!");
				buffer[sublen] = '.';
				++ sublen;
			}
			if (sublen < len){
				// note that we do not ROUND(), we FLOOR() the remainer by casting to integer.
				vprint("%.20f", remainder * 1000000000);
				integer = remainder * pow(10, precision);
				//vnum(integer);
				count = i64_to_charptr(integer, buffer + sublen, len - sublen);
				
				if (count > 0){
					// only return count if all parts of the conversion where a success.
					count += sublen;
				}
			}
		}
	}
	
	vout;
	return count;
}

