//------------------------------------------------
// file:    cast_text.c
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-14
// version: 1.0.1
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: all code to convert a MOLD_TEXT to other MOLD types
//------------------------------------------------

#define VERBOSE
#include "vprint.h"

#include "clibs-cast.h"
#include "clibs-mold.h"
#include "clibs-defines.h"
#include "clibs-enums.h"
#include "clibs-errors.h"
#include "clibs-types.h"


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- GLOBALS
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------
//- cast_text()
//--------------------------
// purpose:  
//
// inputs:   
//
// returns:  
//
// notes:    
//
// to do:    
//
// tests:    
//--------------------------
MoldValue *cast_text(MoldValue *mv, enum MoldTypes type, cbool clone ){
	MoldValue 	*result = NULL;
	MoldValue 	*clonemv = NULL;
	int			 error=SUCCESS;
	
	
	vin("cast_text()");
	if (mv->type != MOLD_TEXT){
		// error not a TEXT !!!
		// we must not merely be of text_based_type... we need to be an actual text.
		error=TRUE;
	}else{
		if (clone) {
			clonemv = make(type); // just create an empty, unbuilt mold value.
			result = clonemv;
		}else{
			result = mv;
		}
		switch(type){
			case MOLD_INT:
				{
					int value = 0;
					error = charptr_to_i32(mv->text.buffer, mv->text.len, &value);
					vnum(value);
					if(! error){
						if (result->owner){
							if (result->text.buffer){
								// release text buffer before we change data within.
								free(result->text.buffer);
								
								result->text.len = 0;
							}
						}
						result->type = MOLD_INT;
						result->value = value;
					}
				}
				break;
				
			default:
				error = ERR_CLIB_CAST_INCOMPATIBLE_DESTINATION_TYPE;
				vprint("unsupported destination type");
				break;
		}
	}
	
	if (error){
		vprint("ERROR! freeing cloned value before returning...");
		// any error condition MUST de-allocate its locally allocated data before exiting from its block.
		// we do not assume to know how to handle the (dynamic, invalid?) transient data within mv here.
		if (clonemv){
			free(clonemv);
		}
		result = NULL;
	}
	
	vout;
	return result;
}
