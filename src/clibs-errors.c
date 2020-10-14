//------------------------------------------------
// file:    clibs-errors.c
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-26
// version: 1.0.0
//
// license: APACHE v2.0 
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: error strings for all aspects of the clib project.
//
// notes:   - some errors will include standard printf codes to identify where to place error message variables (%i, %d, etc.).  
//            these should be replaced by the function which reports the error.  note that this may cause some dynamic
//            memory management to occur.  Care must be taken to identify if a returned string is static or dynamic!
//
//            use the clibs_errors array like so:
//	
//	          clibs_errors[CLIB_ERR_SUCCESS];
//
//------------------------------------------------

















//--------------------------
// this MUST be at line 40
//--------------------------

//--------------------------
//- clibs_errors:
//
// an array of strings detailing each error number.
// 
//--------------------------
char *clibs_errors[] = {
	"All good", //CLIB_ERR_SUCCESS=0, // not an error, all is good
	"Unspecified error", // CLIB_ERR_UNSPECIFIED
	
	// DATA CASTING ERRORS 
	"Cannot cast empty string to integer" // CLIB_ERR_CAST_EMPTY_STRING,
	"Unable to cast value, source data is not appropriate for destination type" //	CLIB_ERR_CAST_INVALID_SRC_VALUE,
};

