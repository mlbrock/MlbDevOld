/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Loads buffers.

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
int TFREAD_ReadBuffer(const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBuffer(file_name, buffer_length, buffer_ptr, error_text)
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(TFREAD_ReadBufferFILE(file_name, buffer_length, buffer_ptr,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadBufferBasic(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferBasic(tfread_ptr, file_name, buffer_length,
	buffer_ptr, error_text)
const STR_CFILE_FUNCS  *tfread_ptr;
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_length;
	unsigned int   count_1;
	char          *tmp_ptr;

	buffer_length = (buffer_length != NULL) ? buffer_length : &tmp_length;

	if ((return_code = TFREAD_ReadBufferRawBasic(tfread_ptr, file_name,
		buffer_length, buffer_ptr, error_text)) == TFREAD_SUCCESS) {
		for (count_1 = 0, tmp_ptr = *buffer_ptr; count_1 < *buffer_length;
			count_1++, tmp_ptr++) {
			if (!(*tmp_ptr))
				*tmp_ptr = ' ';
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

