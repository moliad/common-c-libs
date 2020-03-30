//------------------------------------------------
// file:    clibs-hashing-murmur3.h
// Author:	"Austin Appleby, refactoring & slight mods by Maxim Olivier-Adlhoch"
//
// date:    2011-10-06
// version: 1.0.0
//
// license: Public Domain
//
// purpose: clibs hashing set of libs - this implements in murmur3 hashing.
//
//------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
//------------------------------------------------

#pragma once


//-----------------------------------------------------------------------------

//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- TYPEDEFS
//
//-----------------------------------------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER < 1600)
	// Microsoft Visual Studio
	typedef unsigned char uint8_t;
	typedef unsigned int uint32_t;
	typedef unsigned __int64 uint64_t;

#else  

	// Other compilers
	#include <stdint.h>
#endif // !defined(_MSC_VER)



//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//-  FUNCTION DECLARATIONS
//
// do not edit code beyond this point, it is generated automatically
//-----------------------------------------------------------------------------------------------------------


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- PLATFORM-SPECIFIC FUNCTIONS AND MACROS 
//
//-----------------------------------------------------------------------------------------------------------


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- PART TO IGNORE
//
//-----------------------------------------------------------------------------------------------------------


//-                                                                                                       .
//-----------------------------------------------------------------------------------------------------------
//
//- HASHING FUNCTIONS
//
//-----------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
// copy macro start
extern "C" {
#endif
	// copy macro end

//--------------------------
//-     MurmurHash3_x86_32()
//--------------------------
// purpose:  optimised for x86 architecture, very low latency, best for short data.
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
void MurmurHash3_x86_32 (
	const void * key,    // data to munge
	int len,             // len of given data
    uint32_t seed,       // arbitrary seed value, allows multiple hash keys for the same data, good for bloom filters
    void * out           // address of value to store 32 bit key into
);


//--------------------------
//-     MurmurHash3_x86_128()
//--------------------------
void MurmurHash3_x86_128 ( 
	 const void * key,
	 const int len,
     uint32_t seed, 
	 void * out 
);


//--------------------------
//-     MurmurHash3_x64_128()
//--------------------------
void MurmurHash3_x64_128 ( 
	const void * key, 
	const int len,
    const uint32_t seed, 
	void * out 
);


// copy macro start
#ifdef  __cplusplus
}
#endif
// copy macro end

