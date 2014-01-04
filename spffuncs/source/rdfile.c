/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an SPF definition file.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <tfread.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_ReadDefFile(const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text)
#else
int SPF_ReadDefFile(file_name, buffer_length, buffer_ptr, error_text)
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	if ((return_code = TFREAD_ReadBufferXLateNL(file_name, "\n",
		buffer_length, buffer_ptr, tfread_error_text)) != TFREAD_SUCCESS) {
		nstrcpy(error_text, tfread_error_text, SPF_MAX_ERROR_TEXT - 1);
		return_code = SPF_MAP_ERROR_TFREAD(return_code);
	}

	return(return_code);
}
/*	***********************************************************************	*/

