//------------------------------------------------
// file:    mold.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-08
// version: 1.0.0
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: generic typed dataset serialisation library structures and support code.
//------------------------------------------------

#pragma once

#include "clibs-enums.h"
#include "clib-types.h"


//                                                                         .
//-----------------------------------------------------------------------------------------------------------
//
//- ENUMS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//-     MoldTypes:
//
// mold datatypes, we use these to access methods in the MoldMethods array.
//--------------------------
enum MoldTypes {
	MOLD_VOID=0, // this cannot be used by most functions it implies an un-initialised value..
	MOLD_NONE,
	MOLD_BLOCK,
	MOLD_TEXT,
	MOLD_INT,
	MOLD_WORD,
	MOLD_SET_WORD,
	MOLD_LITERAL,  // use this to add literal text to the result, it can store anything. it is not decorated on mold.
	               // once molded, it may represent several values!
	MOLD_DECIMAL,

	//----
	// we use this to allocate method arrays.
	//----
	MOLD_TYPE_COUNT, // ( 9 )
	
	//----
	// SEMI-TYPES follow
	//
	// These are implemented using MOLD_LITERAL, but are understood in some functions ex:  cast()
	// they cannot be used by build since the system doesn't allow mv->type as semi-types.
	//
	// eventually, we may use the same action functions as MOLD_LITERAL, and just support them directly,
	// but more development is required to proof the idea.
	//
	// some of these may also become their own fully implemented types later on.
	//----
	MOLD_DATE, // (dates may also include time information... it is optional)
	MOLD_TIME,
	MOLD_BINARY,

};

//--------------------------
//-     MoldActions:
//
// action names and offsets, we use these to access methods in the MoldMethods array
//--------------------------
enum MoldActions {
	ACTION_BUILD=0,		// we are given native data to use to set internal data.
	ACTION_CAST,		// convert ourself to another type. may free inner-data, may allocate and return a new MoldValue.
						// return NULL if cast destination is not possible.
	ACTION_APPEND,  	// add data to ourself (may be impossible, in which case we return NULL).
	ACTION_MOLD,    	// output our data into a given char * buffer.
	ACTION_DISMANTLE,	// free memory.
	
	//---
	ACTIONS_COUNT,		// 5
};


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- STRUCTS & ARRAYS
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------
//- MoldMethods:
//
// we store all the methods for all types in a single array.
//
// use the action macros to apply they to any datatype.
//
// some types do not support all actions, in such a case, they are set to a nop function.
//--------------------------
extern void *MoldMethods[];



//--------------------------
//- MoldValue: {...}
//
// data cell for all Mold values.
//--------------------------
typedef struct MoldValue MoldValue;
typedef struct MoldValue MV;
struct MoldValue {
	//--------------------------
	//-     type:
	//--------------------------
	unsigned char type;

	//--------------------------
	//-     owner:
	//
	// are we owner of current data?
	//
	// for some types which are references, we may need to de-allocated data on some actions...
	// this indicates that we are owner of the data, so its our responsability to de-allocate when
	// the data is not used anymore.
	//--------------------------
	unsigned char owner;

	//--------------------------
	//-     newline:
	//
	// do we add a newline after this value while molding?
	// doesn't affect block types, which always add a newline
	//--------------------------
	unsigned char newline;

	//--------------------------
	//-     reserved2:
	//
	// may be used in future if we need extra specs
	//--------------------------
	unsigned char reserved2;

	//--------------------------
	//-     next:
	//--------------------------
	MoldValue	*next;

	//-     Union { ??? }
	union {
		//--------------------------
		//-         value:
		//--------------------------
		int 		 value;

		//--------------------------
		//-         text: {...}
		//--------------------------
		struct {
			//--------------------------
			//-             buffer:
			//
			// the MolvValue.owner value above will determine if we need to
			// free the buffer on any call to dismantle.
			//
			// if we are not the owner, then we just forget about the buffer
			// and assume an external piece of code is responsible for its memory.
			//--------------------------
			char *buffer;
			

			//--------------------------
			//-             len:
			//
			// note that len DOES NOT include null termination.
			//
			// thus the actual size of buffer is len + 1
			//--------------------------
			int len;
		} text;

		//--------------------------
		//-         child: {...}
		//--------------------------
		struct {
			//--------------------------
			//-             head:
			//--------------------------
			MoldValue	*head; // note head and tail CAN be the same value (they can also both be NULL)

			//--------------------------
			//-             tail:
			//--------------------------
			MoldValue	*tail;
		} child;

		//--------------------------
		//-         decimal:
		//--------------------------
		double		 decimal;
	};
};

typedef struct MysrBlock MysrBlock;


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- GLOBAL DECLARATIONS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//- __mvptr:
//
// this will be used in expressions as a temporary pointer.
//--------------------------
extern MoldValue *__mvptr;
extern void *__func;


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- HELPER FUNCTIONS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//-     mold_type()
//--------------------------
const char *mold_type(MoldValue* mv);
	

//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- ACTION FUNCTION ENTRY POINTS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//-     make()
//--------------------------
// purpose:  allocate and setup an empty or null MoldValue
//--------------------------
MoldValue *make(int type);


//--------------------------
//-     build()
//--------------------------
MoldValue *build(int type, void *data);


//--------------------------
//-     frame()
//--------------------------
MoldValue *frame(int type, void *data);


//--------------------------
//-     mold()
//--------------------------
int mold(MoldValue *value, char *buffer, int buffer_size, int indents);


//--------------------------
//-     cast()
//--------------------------
MoldValue *cast(MoldValue *mv,  int new_type, cbool clone);


//--------------------------
//-     append()
//--------------------------
MoldValue *append(MoldValue* series, MoldValue* value);


//--------------------------
//-     load()
//--------------------------
MoldValue* load (char *text);


//--------------------------
//-     dismantle()
//--------------------------
void dismantle(MoldValue *mv);


//--------------------------
//-     dismantle_list()
//--------------------------
int dismantle_list(MoldValue *mv);


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- MACROS
//
//-----------------------------------------------------------------------------------------------------------




