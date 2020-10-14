//------------------------------------------------
// file:    clibs-vprint.c
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
//------------------------------------------------

#include "clibs-vprint.h"

char verbose_indentation[verbose_array_size] = {0}; // = "";
int verbose_indentations   =  0;


int do_verbose = 0;
int do_vlog    = 0;

char *vlogpath = NULL;
FILE *vlogfile = NULL; // if a file is setup for logging, vlogon will open it and assign the file pointer here.


void update_verbose_indentations (){
	//printf("%h", verbose_indentation);
	if (verbose_indentations < 0){
		printf("=================\nERROR!!! trace depth is negative!!!!\n reset to zero... fix sources to remove this warning.\n=================\n");
		verbose_indentations = 0;
	}
	if (verbose_indentations * verbose_tabs  > (verbose_max_depth * verbose_tabs)) {
		printf("ERROR!!! PAST VPRINT TRACE DEPTH ALLOWANCE\n application will quit after you press enter.");
		//_getch();
		exit(EXIT_FAILURE);
	}
	memset(verbose_indentation, ' ', (verbose_indentations * verbose_tabs));
	verbose_indentation[verbose_indentations * verbose_tabs] = '\0';
}


