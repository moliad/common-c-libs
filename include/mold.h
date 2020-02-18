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
	MOLD_NONE=0,
	MOLD_BLOCK,
	MOLD_TEXT,
	MOLD_INT,
	MOLD_WORD,
	MOLD_SET_WORD,
	
	//----
	// we use this to allocate method arrays.
	MOLD_TYPE_COUNT, // 6

	// these are not yet implemented.
	MOLD_DECIMAL,
};

//--------------------------
//-     MoldActions:
//
// action names and offsets, we use these to access methods in the MoldMethods array
//--------------------------
enum MoldActions {
	MOLD_BUILD=0,  // we are given native data to use to set internal data.
	MOLD_CAST,     // convert ourself to another type. may free inner-data, doesn't allocate a new MoldValue.
	               // return NULL if cast destination is not possible.
	MOLD_APPEND,   // add data to ourself (may be impossible, in which case we return NULL).
	MOLD_MOLD,     // output our data into a given char * buffer.
	
	//---
	MOLD_ACTIONS_COUNT, // 4
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
	//-     reserved1:
	//
	// may be used in future if we need extra specs
	//--------------------------
	unsigned char reserved1;

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
			// note that any data stored in buffer is ALWAYS
			// allocated via build. so there is never a reference
			// to data owned by code outside the MoldValue itself.
			//
			// when MoldValue is destroyed, this buffer is always
			// freed.
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
//-     mold()
//--------------------------
// purpose:  converts the given value to a string within the given buffer.
//
// inputs:   
//
// returns:  number of chars appended to buffer (always bound by given buffer_size)
//
// notes:    - before calling mold, be sure to increase pointer to buffer and decrease buffer_size as you call mold on a list of values.
//           - mold is safe for use recursively (we supply all contextual values on stack).
//
// to do:    
//
// tests:    
//--------------------------
int mold(MoldValue *value, char *buffer, int buffer_size, int indents);


//--------------------------
//-     append()
//--------------------------
MoldValue *append(MoldValue* series, MoldValue* value);


//--------------------------
//-     load()
//--------------------------
MoldValue* load (char *text);


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- MACROS
//
//-----------------------------------------------------------------------------------------------------------




