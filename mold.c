//------------------------------------------------
// file:    mold.c
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-14
// version: 1.0.1
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: generic typed dataset serialisation library functions and reference class instances
//------------------------------------------------

#include "mold.h"
#include <stdio.h>
#include <string.h>

#define VERBOSE
#include "vprint.h"
#include "core-defines.h"
#include "clibs_cast.h"

//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- GLOBALS
//
//-----------------------------------------------------------------------------------------------------------

int iii = 66;

int allocated_values = 0;
//--------------------------
//- __mvptr:
//
// this will be used in expressions as a temporary pointer.
//--------------------------
MoldValue *__mvptr=NULL;

//--------------------------
//- __func:
//
// this will be used in expressions as a temporary pointer.
//--------------------------
void * __func=NULL;


//data=make(Block, gg);
//data->methods->append(make (None));



//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- HELPER FUNCTIONS
//
//-----------------------------------------------------------------------------------------------------------
//--------------------------
//-     is_series()
//--------------------------
// purpose:  determine if a value is a series supporting any series code.
//
// inputs:
//
// returns:  0 for false, 1 for true
//
// notes:    currently could just be and if, but we set it up for later, when there may be several series type.
//
// to do:
//
// tests:
//--------------------------
int is_series(MoldValue* mv){
	int result=0;
	//vin("is_series()");
	switch (mv->type){
		case MOLD_BLOCK:
			result=1;
			break;
		default:
			result=0;
			break;
	}
	//vout;
	return result;
}


//--------------------------
//-     is_text_based()
//--------------------------
// purpose:  determine if a mold value is based on a char * value set within text attribute.
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
int is_text_based(MoldValue *mv){
	int result=0;

	vin("is_text_based()");
	switch (mv->type){
		case MOLD_TEXT:
		case MOLD_WORD:
		case MOLD_SET_WORD:
			result=1;
			break;
		default:
			result=0;
			break;
	}
	vout;
	return result;
}


//--------------------------
//-     is_int()
//--------------------------
// purpose:  determine if a mold value is based on an int * value.
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
int is_int(MoldValue *mv){
	int result=0;

	vin("is_int()");
	result = (mv->type == MOLD_INT);

	vout;
	return result;
}


//--------------------------
//-     probe()
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
char* probe(MoldValue* value){
	char* string = NULL;
	vin("probe()");

	vout;

	return string;
}


//--------------------------
//-     mold_type()
//--------------------------
// purpose:  dumps the type of a moldvalue to stdout.
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
const char *mold_type(MoldValue* mv){
	//vin("mold_type()");
	char *str="Invalid!";

	if (mv){
		switch(mv->type){
			case MOLD_NONE:
				str = "None!";
				break;
			case MOLD_BLOCK:
				str = "Block!";
				break;
			case MOLD_TEXT:
				str = "Text!";
				break;
			case MOLD_INT:
				str = "Integer!";
				break;
			case MOLD_WORD:
				str = "Word!";
				break;
			case MOLD_SET_WORD:
				str = "SetWord!";
				break;
			default:
				str = "Unknown!";
				break;
		}
	}

	//vout;
	return str;
}


//--------------------------
//-     mold_indents()
//--------------------------
int mold_indents(char *buffer, int len, int indents){
	int i=0;
	//vin("mold_indents()");
	for(i=0; i<(indents * 4); i++){
		if (i < len){
			buffer[i] = ' ';
		}else{
			break;
		}
	}
	//vnum(indents);
	//vout;
	return i;
}


//--------------------------
//-     get_method()
//--------------------------
void *get_method( MoldValue *mv, int action ){
	void *func=NULL;
	int i=0;

	//vin("get_method()");

	//vnum(action);
	//vnum(mv->type);

	if (action > ACTIONS_COUNT){
		vprint("get_method() ERROR!! invalid action %i", action);
	}else{
		if (mv->type > MOLD_TYPE_COUNT){
			vprint ("get_method() ERROR!! invalid Mold value");
		}else{

			i = (mv->type * ACTIONS_COUNT) + action;
			func = MoldMethods[ i ];
		}
	}
	//vout;

	return func;
}


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- MOLD ACTION FUNCTIONS
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------
//-     no_op_build()
//--------------------------
// purpose:  used for all types which have no specific initialisation to do.
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
MoldValue *no_op_build(
	MoldValue *value,
	void *data,
	int owner
){
	vin("no_op_build()");
	vnum(value->type);
	vout;
	return value;
}






//--------------------------
//-     mold_none()
//--------------------------
// purpose:
//
// inputs:
//
// returns:  length of text (without nul termination)
//
// notes:    always null terminates the result.
//
// to do:
//
// tests:
//--------------------------
int mold_none(MoldValue *value, char *buffer, int len, int indents ){
	int result=0;
	vin("mold_none()");
	if (len > 7){
		memcpy(buffer, "#[none]", 7);
		buffer[7]=0;
		result = 7;
	}
	vnum(result);
	vout;
	return result;
}


//--------------------------
//-     append_block()
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
MoldValue* append_block( MoldValue* block, MoldValue* value ){
	vin("append_block()");
	if (block->child.head == NULL){
		block->child.head = value;
		block->child.tail = value;
	}else{
		block->child.tail->next = value;
		block->child.tail = value;
	}
	vout;
	return block;
}


//--------------------------
//-     mold_block()
//--------------------------
// purpose:
//
// inputs:
//
// returns: length of text (without nul termination)
//
// notes:
//
// to do:
//
// tests:
//--------------------------
int mold_block(MoldValue* value, char *buffer, int len, int indents){
	//int result=0;
	int sublen=0;
	MoldValue* subvalue;

	vin("mold_block()");

	// make sure we get proper arguments.
	if ((len > 0) && (buffer != NULL)){

		if (len >= 3){
			buffer[0] = '[';
			buffer[1] = '\n';
			sublen    = 2;
			indents += 1;
			sublen += mold_indents(buffer + sublen, len - sublen, indents);
			subvalue = value->child.head;
			if (subvalue){
				do{
					sublen += mold(subvalue, buffer + sublen, len - sublen, indents );

					// add a space if there is another item to mold.
					subvalue = subvalue->next;
					if (subvalue) {
						if ( (sublen + 1) < len ){
							buffer[sublen] = ' ';
							++ sublen;
						}
					}
				}
				while(subvalue);
			}
			if ( (sublen + 1) < len ){
				buffer[sublen] = '\n';
				sublen ++;
			}
			indents -= 1 ;
			sublen += mold_indents(buffer + sublen, len - sublen, indents);
			if ( (sublen + 1) < len ){
				buffer[sublen ] = ']';
				sublen ++;
			}
			sublen += mold_indents(buffer + sublen, len - sublen, indents);
			if ( (sublen + 1) < len ){
				buffer[sublen] = '\n';
				sublen ++;
			}
		}
		// whatever happens, nul terminate result.
		if (sublen < len){
			buffer[sublen]=0;
		}else{
			buffer[len - 1] = 0;
		}
		//vnum(sublen);
		//vstr(buffer);
	}
	vout;
	return sublen;
}


//--------------------------
//-     mold_int()
//--------------------------
// purpose:
//
// inputs:
//
// returns:  length of text (without nul termination)
//
// notes:
//
// to do:
//
// tests:
//--------------------------
int mold_int(MoldValue *mv, char *buffer, int len, int indents ){
	int result=0;

	vin("mold_int()");

	result = i32_to_charptr(mv->value, buffer, len);

	vnum(result);
	vout;
	return result;
}


//--------------------------
//-     build_text_based_value()
//--------------------------
// purpose:
//
// inputs:   owner is non-0 if we must copy the data. 0 if we should refer to it (and NOT deallocate it).
//
// returns:
//
// notes:    If given data is not a null-terminated string, this function will corrupt application.
//
// to do:
//
// tests:
//--------------------------
MoldValue *build_text_based_value(MoldValue *mv, const char *data, int owner){
	int len=0;
	char *buffer =NULL;
	vin("build_text_based_value()");

	if (is_text_based(mv)) {
		len = strlen(data);
		if (owner){
			buffer = malloc(len + 1);
			memcpy(buffer, data, len);
			mv->owner = TRUE;

			// force null termination;
			buffer[len] = 0;
			mv->text.buffer = buffer;
		}else{
			mv->owner = FALSE;
			mv->text.buffer = data;
		}
		mv->text.len = len;
	}
	vout;
	return mv;
}


//--------------------------
//-     build_int_value()
//--------------------------
// purpose:
//
// inputs:   owner is non-0 if we must copy the data. 0 if we should refer to it (and NOT deallocate it).
//
// returns:
//
// notes:
//
// to do:
//
// tests:
//--------------------------
MoldValue *build_int_value(MoldValue *mv, int *data, int owner){
	int len=0;
	char *buffer =NULL;
	vin("build_int_value()");

	if (is_int(mv)) {
		mv->value = *data;
	}
	vout;
	return mv;
}


//--------------------------
//-     mold_text()
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
int mold_text(MoldValue *mv, char *buffer, int len, int indents ){
	int sublen = 0;
	int i=0;
	char letter=0;
	int safelen =0;

	vin("mold_text()");
	safelen = len - 1;

	if (mv->text.buffer == NULL){
		// we received a null string, so we'll return a none!
		sublen = mold_none(mv, buffer, len, indents);
	}else{
		// two bytes are enough for an empty string
		if (safelen >= 2){
			buffer[0] = '{';
			sublen ++;

			for(i=0; i < mv->text.len; i++){
				letter = mv->text.buffer[i];
				if (
					   letter == '{'
					|| letter == '}'
					|| letter == '^'
				){
					// we need to escape the result
					if (sublen < safelen){
						buffer[sublen] = '^';
						sublen++;
					}
				}

				if (sublen < safelen){
					buffer[sublen] = letter;
					sublen ++;
				}
			}

			if (sublen < safelen){
				buffer[sublen] = '}';
				sublen ++;
			}

			// sublen can NEVER be as large as len... it must reserve space for nul termination.
			buffer[sublen] = 0;
		}
	}
	vout;
	return sublen;
}




//--------------------------
//-     mold_word()
//--------------------------
int mold_word(MoldValue *mv, char *buffer, int len, int indents){
	vin("mold_word()");
	if (len > mv->text.len){
		memcpy(buffer, mv->text.buffer, mv->text.len);
		buffer[len] = 0;
	}
	vout;
	return mv->text.len;
}

//--------------------------
//-     mold_set_word()
//--------------------------
int mold_set_word(MoldValue *mv, char *buffer, int len, int indents){
	vin("mold_set_word()");
	if (len > ( mv->text.len + 1)){
		memcpy(buffer, mv->text.buffer, mv->text.len);
		buffer [mv->text.len] = ':';
		buffer[mv->text.len + 1] = 0;
	}
	vout;
	return mv->text.len + 1;
}





//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- ACTION TABLE
//
//-----------------------------------------------------------------------------------------------------------



//--------------------------
//-     MoldMethods:
//--------------------------
void *MoldMethods[ ACTIONS_COUNT * MOLD_TYPE_COUNT ] = {
	//----------------
	// action order:
	//
	// BUILD   CAST   APPEND   MOLD   DISMANTLE
	//----------------

	// MOLD_NONE
	no_op_build, NULL, NULL, mold_none, NULL,

	// MOLD_BLOCK
	no_op_build, NULL, append_block, mold_block, NULL,

	// MOLD_TEXT
	build_text_based_value, NULL, NULL, mold_text, NULL,

	// MOLD_INT
	build_int_value, NULL, NULL, mold_int, NULL,

	// MOLD_WORD
	build_text_based_value, NULL, NULL, mold_word, NULL,

	// MOLD_SET_WORD
	build_text_based_value, NULL, NULL, mold_set_word, NULL,
};



//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- ACTION ENTRY POINTS
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------
//-     make()
//--------------------------
// purpose:  allocate and setup an empty or null MoldValue
//--------------------------
MoldValue *make(int type){
	MoldValue *mvptr;

	vin("make()");
	mvptr=calloc(1, sizeof(MoldValue) );

	if(mvptr != NULL) {
		mvptr->type = type;
	}
	vprint("%s = %p ", mold_type(mvptr), mvptr );
	++allocated_values;
	vout;

	return mvptr;
}





//--------------------------
//-     build()
//--------------------------
// purpose:  create and initialise a mold value with some data
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
MoldValue *build(int type, void *data){
	MoldValue *mv;
	MoldValue *(*bldfunc)(MoldValue*, void *, int);  // declare function pointer.

	vin("build()");

	mv = make(type);
	vprint("%s", mold_type(mv));

	if (mv){
		bldfunc = get_method(mv, ACTION_BUILD);
		//vprint("got function!");
		//vptr(bldfunc);
		if (bldfunc){
			mv = bldfunc(mv, data, 1);
		}
	}
	vout;

	return mv;
}


//--------------------------
//-     frame()
//--------------------------
// purpose:  build a MoldValue, but do not own the data (we refer to it and must not de-allocate)
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
MoldValue *frame(int type, void *data){
	MoldValue *mv;
	MoldValue *(*bldfunc)(MoldValue*, void *, int);  // declare function pointer.

	vin("frame()");

	mv = make(type);
	vprint("%s", mold_type(mv));

	if (mv){
		bldfunc = get_method(mv, ACTION_BUILD);
		//vprint("got function!");
		//vptr(bldfunc);
		if (bldfunc){
			mv = bldfunc(mv, data, 0);
		}
	}
	vout;

	return mv;
}


//--------------------------
//-     append()
//--------------------------
// purpose:  insert a value AFTER the given series.
//
// inputs:
//
// returns:  returns given value if append was successful. this may be the last item in series.
//
// notes:    - if given series is not really a series, the return value is NULL.
//           - we do NOT iterate to tail of series. that must be done manually.
//
// to do:
//
// tests:
//--------------------------
MoldValue *append(MoldValue* series, MoldValue* value){
	MoldValue *result = NULL;

	MoldValue*(* appendfunc)(MoldValue*, MoldValue*);


	//vin("append()");

	//vprint("appending value %p to series %p",value, series);
	if (value && series){
		if (is_series(series)) {

			if ((appendfunc = get_method(series, ACTION_APPEND))){
				appendfunc(series, value);
			}
		}
	}
	//vout;
	return result;
}


//--------------------------
//-     mold()
//--------------------------
// purpose:  converts the given value to a string within the given buffer.
//
// inputs:   when calling from the main code, set indents to 0.
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
int mold(MoldValue *value, char *buffer, int buffer_size, int indents){
	int result=0;
	int (*moldfunc)(MoldValue*, char*, int, int);  // declare function pointer.

	//vin("mold()");

	//vptr(value);
	moldfunc = get_method(value, ACTION_MOLD);

	if (moldfunc){
		result = moldfunc(value, buffer, buffer_size, indents);
	}

	//vout;
	return result;
}




//--------------------------
//-     dismantle()
//--------------------------
// purpose:  free all the data within a mold value if it is owned and free the mold value itself.
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
void dismantle(MoldValue *mv){
	vin("dismantle()");

	vout;
}



//--------------------------
//-     load()
//--------------------------
// purpose:  given a piece of text, build a MoldValue with parsed data
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
MoldValue* load (char *text){
	vin("load()");

	vout;
	return NULL;
}













