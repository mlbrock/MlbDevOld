/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads lines from a file without per-line allocation
								using the 'FILE' facility.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadLinesNoAllocFILE(const char *file_name, unsigned int *line_count,
	char ***line_list, char *error_text)
#else
int TFREAD_ReadLinesNoAllocFILE(file_name, line_count, line_list, error_text)
const char     *file_name;
unsigned int   *line_count;
char         ***line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	STR_CFILE_FUNCS cfile_funcs;

	return(TFREAD_ReadLinesNoAllocBasic(TFREAD_GetDefDataFILE(&cfile_funcs),
		file_name, line_count, line_list, error_text));
}
/*	***********************************************************************	*/


