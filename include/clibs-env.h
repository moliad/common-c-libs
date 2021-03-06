//------------------------------------------------
// file:    clibs-env.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-03-08
// version: 1.0.0
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: Compiler and platform-specific environment management
//------------------------------------------------

#pragma once


//---------------------------------------
//  Compiler detection
//
//  we unify the naming scheme accross compilers, so its cleaner in the code.
//
//  furthermore, we can detect, fix or invalidate specific compiler/os pairs or
//  other invalid compiler setups.
//---------------------------------------

#ifdef _MSC_VER
	#define IS_MSVC_COMPILER
#elif (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
	#define IS_GCC_COMPILER
	#define IS_GCC_COMPATIBLE_COMPILER
#elif defined(__clang__)
	#define IS_CLANG_COMPILER
	#define IS_GCC_COMPATIBLE_COMPILER
#else
	#error "UNSUPORTED COMPILER, edit and extend the  clibs-env.h  header file."
#endif




//---------------------------------------
//  Compiler abstraction
//
//  Define macros which adapt based on the current compiler.
//
//  These must be defined before anyhting else since we use some of these even in this file later.
//
//  Also note that if you add support for another compiler, you MUST add all macros for it.
//---------------------------------------

//------------
// these macros are just for this file... they are not used outside of it.
#define CLIB_ENV_STRINGIFY2__(x) #x
#define CLIB_ENV_STRINGIFY1__(x) CLIB_ENV_STRINGIFY2__(x)

//------------
// these macros must ALL be defined and adapted for any new compiler or incompatible new version of a compiler.
#ifdef IS_MSVC_COMPILER
	//----
	// compiler neutral warning
	//#define CLIB_ENV_LOC__ __FILE__ "(" CLIB_ENV_STRINGIFY1__(__LINE__) ") : warning Msg: "
	#define COMPILER_WARNING(msG) __pragma(message(__FILE__ "(" CLIB_ENV_STRINGIFY1__(__LINE__) ") : warning Msg: " #msG))	

#elif IS_GCC_COMPATIBLE_COMPILER 
	#define CLIB_DO_PRAGMA(x) _Pragma (#x)
	// ** NOTE THE GCC CODE BELOW IS UNTESTED **
	//----
	// compiler neutral warning
	#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 8)
		#define COMPILER_WARNING(msG) CLIB_DO_PRAGMA( GCC warning #msG) )
	#else
		#define COMPILER_WARNING(msG) CLIB_DO_PRAGMA( message ("WARNING - " #msG) )
	#endif
#endif





//---------------------------------------
//  OS & platform identification
// 
//  clean and uniform naming scheme
//
//  we also detect, merge and invalidate some platforms.
//  
//  if your platform is not supported, we raise a compile error
//---------------------------------------
#ifdef _WIN64 //define something for Windows (64-bit)
	#define IS_WIN64_PLATFORM
	
#elif _WIN32 //define something for Windows (32-bit)
	#define IS_WIN32_PLATFORM
	
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR // iOS Simulator
    	#define IS_IOS_PLATFORM

    #elif TARGET_OS_IPHONE // iOS device
    	#define IS_IOS_PLATFORM
    
    #elif TARGET_OS_MAC // Other kinds of Mac OS
    	#define IS_OSX_PLATFORM
    
    #else
        #error "Unsupported Apple Platform"
    
    #endif
    
#elif __linux // linux in general
 	#define IS_LINUX_PLATFORM
   
#elif __unix  // all unices not caught above
 	#define IS_UNIX_PLATFORM
    
#elif __posix // POSIX
 	#define IS_POSIX_PLATFORM
    
#else
    #error "unknown Platform, not supported by clibs."
	
#endif


