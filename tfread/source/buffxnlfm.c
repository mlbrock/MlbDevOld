/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads a buffer with new-line translation using the
								'MFILE' facility.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
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
int TFREAD_ReadBufferXLateNLMFILE(const char *file_name, const char *nl_string,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferXLateNLMFILE(file_name, nl_string, buffer_length,
	buffer_ptr, error_text)
const char    *file_name;
const char    *nl_string;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	STR_CFILE_FUNCS cfile_funcs;

	return(TFREAD_ReadBufferXLateNLBasic(TFREAD_GetDefDataMFILE(&cfile_funcs),
		file_name, nl_string, buffer_length, buffer_ptr, error_text));
}
/*	***********************************************************************	*/


