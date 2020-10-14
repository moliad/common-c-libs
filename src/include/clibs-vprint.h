//------------------------------------------------
// file:    clibs-vprint.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-10-13
// version: 1.0.0
//
// license: APACHE v2.0 
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: a set of macros which define switchable, stacked tracing.
//          when VDEBUG is set to false, all tracing disapears.
//
//------------------------------------------------

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "clibs-macros-src.h"

extern char verbose_indentation[];
int verbose_indentations;
int do_verbose;
int do_vlog;

void update_verbose_indentations ();

char *vlogpath; // if set to a string, we will ALSO dump the vprinting in that file.
FILE *vlogfile;    // if vlogpath is setup, von will attempt to open it for write and dump the file ptr here.



//-------
// Setup vprint activation
//
// Allows each module to choose if they wish to implement vprint separately (but its not switchable
// after compilation).
//
// if you #define VERBOSE in the app's IDE or makefile, the whole app will verbose print.
//
// if you #define VERBOSE above, all modules of all apps will vprint.
//
// you can also #define VERBOSE directly within a module's .C file so that only IT enables VERBOSITY...
//
// you can use the VPRINT_OFF define to deactivate it within a specific source file, 
// VPRINT_OFF has precedence over VERBOSE, so it will cancel vprinting, even if enabled globally.
//
// REMEMBER to setup verbosity BEFORE loading the VPRINT headers.
//
// ALSO REMEMBER that you need to add the clibs-vprint.c file to your project to link its object file.
//
// whatever you do, they still all share the same vprint indentation stack.
//-------
// #ifnef VERBOSE
//     #define VERBOSE
// #endif
//-------

#ifndef VERBOSE
	#define IS_NOT_VPRINTING
#else
	#ifdef VPRINT_OFF
		#define IS_NOT_VPRINTING
	#else
		#define IS_VPRINTING
	#endif
#endif


//--------------------------
//- FLUSH_STDIO
//
// Uncomment the following line to trigger unbuffered i/o for vprint, 
// we will flush the buffer after each vprint call.
//--------------------------
#define FLUSH_STDIO
//--------------------------



//--------------------------
//-  BUFFERED_VLOG
//
// define the following in your make files or projects, to allow FAST DISK logging.
//
// this is off by default because we need the vlogs to flush at each call to vprint
// otherwise, the data within the i/o buffer doesn't get flushed to disk when an
// exception occurs, so we have no clue, in the log, where the error occured.
//
// setting the define below, will open the file in normal, buffered i/o, which is
// MUCH faster (basically speed of disk), in cases where you want to trace a
// non-crashing, but very long trace without waiting hours for it.
//
// this is especially true when the large loops are being used.
//
// #define BUFFERED_VLOG
//--------------------------


#define verbose_max_depth 250  // more than enough.. at this point we are pretty sure to be in error loop.
#define verbose_tabs 4
#define verbose_array_size 1000 // THIS MUST BE ASSIGNED to ( max_depth * tabs ). it is used to declare the indentation array.





#ifdef IS_NOT_VPRINTING
	//COMPILER_WARNING(not vprinting!!)

	// all of these consume the inputs and nothing is actually embeded in the final source.
	#define vindent()
	#define vin(...) // nothing is printed.
	#define vprint(...) // nothing is printed.
	#define vprin(...) // nothing is printed.
	#define vline(...)
	#define vnum(...)
	#define vstr(...)
	#define vchar(...)
	#define vhex(...)
	#define vptr(...)
	#define vbits(...)
	#define vout
	#define von
	#define voff
	#define vlog(...)
	#define vlogon
	#define vlogoff
	#define vreturn return
	#define vreset()
	#define vlogreset

#endif


#ifdef IS_VPRINTING
	//COMPILER_WARNING(is vprinting!!)

	// the following are exclusively used if/when a file log is setup
	#if defined(FLUSH_STDIO)
		#define vflush() fflush(stdout)
	#else
		#define vflush() () // empty expression
	#endif

	#define if_verbose(expr) if (do_verbose != 0){expr}
	#define if_vlog(expr) if ((do_vlog != 0) && (vlogfile != NULL)){expr}

	#define ventab()    {verbose_indentations++ ; update_verbose_indentations();}
	#define vdetab()    {verbose_indentations-- ; update_verbose_indentations();}
	#define vreset()    {verbose_indentations = 0 ; update_verbose_indentations();}

	#define vindent()   if_verbose( printf("%s",verbose_indentation);) if_vlog ( fprintf(vlogfile, "%s",verbose_indentation);               )
	#define vin(...)    vindent(); if_verbose( printf(__VA_ARGS__); printf(" [\n");) vflush(); if_vlog ( fprintf(vlogfile, __VA_ARGS__); fprintf(vlogfile, " [\n"); ) ventab()
	#define vprint(...) vindent(); if_verbose( printf(__VA_ARGS__); printf("\n");) vflush(); if_vlog ( fprintf(vlogfile, __VA_ARGS__); fprintf(vlogfile, "\n");  fflush(vlogfile); )
	#define vline()     vprint("\n")
	#define vprin(...)  if_verbose( printf(__VA_ARGS__); ) vflush(); if_vlog ( fprintf(vlogfile, __VA_ARGS__);                            )
	#define vnum(var)   vprint( QUOTE(var) ": %d", var)
	#define vstr(var)   vprint( QUOTE(var) ": %s", var)
	#define vchar(var)   vprint( QUOTE(var) ": %c", var)
	#define vhex(var)   vprint( QUOTE(var) ": %.8X", var)

//	#ifdef IS_64BIT_BUILD
//		#define vptr(var)   vprint( QUOTE(var) ": %.16x", (unsigned long long int )var);
//	#else
//		#define vptr(var)   vprint( QUOTE(var) ": %.8x", (unsigned int) var);
//	#endif

	#define vptr(var)   vprint( QUOTE(var) ": %p", var);


	#define vbits(var)  vprint( QUOTE(var) ": %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d", \
		( 0 != (var & (1 << 27))), ( 0 != (var & (1 << 26))), ( 0 != (var & (1 << 25))), ( 0 != ( var & (1 << 24))), \
		( 0 != (var & (1 << 23))), ( 0 != (var & (1 << 22))), ( 0 != (var & (1 << 21))), ( 0 != ( var & (1 << 20))), \
		( 0 != (var & (1 << 19))), ( 0 != (var & (1 << 18))), ( 0 != (var & (1 << 17))), ( 0 != ( var & (1 << 16))), \
		( 0 != (var & (1 << 15))), ( 0 != (var & (1 << 14))), ( 0 != (var & (1 << 13))), ( 0 != ( var & (1 << 12))), \
		( 0 != (var & (1 << 11))), ( 0 != (var & (1 << 10))), ( 0 != (var & (1 << 9))),  ( 0 != ( var & (1 << 8))), \
		( 0 != (var & (1 << 7))),  ( 0 != (var & (1 << 6))),  ( 0 != (var & (1 << 5))),  ( 0 != ( var & (1 << 4))), \
		( 0 != (var & (1 << 3))),  ( 0 != (var & (1 << 2))),  ( 0 != (var & (1 << 1))),  ( 0 != (var & 1)) \
	)

	#define vout        vdetab(); vprint("]");
	#define von         {do_verbose = 1;}
	#define voff        {do_verbose = 0;}
	#define vreturn     vout; return

	// the following are exclusively used if/when a file log is setup
	#if defined(BUFFERED_VLOG)
		#define VLOG_FILEMODE "a"  // be carefull, the data file is not flushed automatically, when looking at it, it may be missing a big chunk of the last vprints.
	#else
		#define VLOG_FILEMODE "ac" // the "c" file mode is to force fflush() to write to disk immediately. (this allows mtail to properly trace the files) see: http://msdn.microsoft.com/en-us/library/0sewbhc7.aspx
	#endif
	#define vlogon      {do_vlog = 1;  if (vlogpath != NULL){ vlogfile = fopen(vlogpath, "ac"); } }
	#define vlogoff     {do_vlog = 0;  if (vlogfile != NULL) { fclose(vlogfile); vlogfile = NULL; } }
	#define vlog(...)   if_vlog ( fprintf(vlogfile, __VA_ARGS__); fprintf(vlogfile, "\n");   )
	#define vlogreset   if (vlogpath != NULL){ vlogfile = fopen(vlogpath, "w"); fclose(vlogfile); vlogfile = NULL; }
#endif

