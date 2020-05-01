//------------------------------------------------
// file:      clibs-compile-setup.h
// author:    Maxim Olivier-Adlhoch
// copyright: Maxim Olivier-Adlhoch
//
// date:      2020-04-30
// version:   0.1.0
//
// license:   APACHE v2.0
//            https://www.apache.org/licenses/LICENSE-2.0
//
// purpose:  - configurations which are used to setup your app source before compiling.
//           - multiple tools may re-use the same configs, so its easier to manage all of them
//------------------------------------------------
#pragma once


// use this to make sure this file is loaded in your code.
#define CLIBS_COMPILE_SETUP


//-----------------------------------
//- ENDIANNESS CONTROL
//-----------------------------------
// if you are compiling on a big endian platform, just uncomment the following define
//
// various files will adapt, where it counts.
//
// when not defined here, we assume the platform is little endian.
//-----------------------------------
// #define IS_BIG_ENDIAN
// #define IS_LITTLE_ENDIAN

#ifndef IS_LITTLE_ENDIAN
	#ifndef IS_BIG_ENDIAN
		#ifdef IS_WINDOWS_PLATFORM
			// all reasonably recent versions of windows (intel + arm) run in little endian mode.
			// we assume no more MIPS Windows NT machines will run this code.
			// if so, just extend to make it work.
			#define IS_LITTLE_ENDIAN

		#elif defined(IS_GCC_COMPILER)
			#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				#define IS_LITTLE_ENDIAN
			#else if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
				#define IS_BIG_ENDIAN
			#endif
		#endif
	#endif
#endif

//---------
// make sure our current setup triggers one of the above conditionals
//---------
#ifndef IS_LITTLE_ENDIAN
	#ifndef IS_BIG_ENDIAN
		#error "PLATFORM ENDIANNESS ISN'T DEFINED"
	#endif
#endif


//-----------------------------------
//- GRIND_MEMORY
//
// enables drastic, barbaric memory management, can be enabled, even when not in debug mode.
//
// recompile with this enabled, when the CRT detects a heap corruption. 
// it should then immediately trap the error AT THE POINT OF ORIGIN, as opposed to the point of detection.
//
// Note that this system ALSO detects overflow ** READs ** which cannot be detected by normal debugger tooling.
//
// You can optionally set this define in your compiler to activate it in a specific target.
//-----------------------------------
//#define GRIND_MEMORY


//-----------------------------------
//- GRIND_BOTTOM
//
// grinding checks for underflows (rare) rather than overflows.
//
// (has no effect if GRIND_MEMORY is undefined)
//-----------------------------------
//#define GRIND_BOTTOM

