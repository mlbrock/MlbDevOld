/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Puts a string into a memory-mapped file.

	Revision History	:	1992-09-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mputs

   SYNOPSIS    :  return_code = mputs(put_string, mfile_ptr);

						int          return_code;

						const char  *put_string;

						MFILE       *mfile_ptr;

   DESCRIPTION :  Places a string into a memory-mapped file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``put_string`` is a pointer to the string to be placed
						into the memory-mapped file.

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) The number of characters placed into the
						memory-mapped file if successful.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fputs()``.

   CAVEATS     :  

   SEE ALSO    :  mgets

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mputs
						Memory-mapped File Functions:mputs
						MFILE Functions:mputs

	PUBLISH XREF:	mputs

	PUBLISH NAME:	mputs

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mputs(const char *put_string, MFILE *mfile_ptr)
#else
int mputs(put_string, mfile_ptr)
const char  *put_string;
MFILE       *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int          return_value = EOF;
	unsigned int string_length;

	if ((string_length = strlen(put_string)) == 0)
		return_value = 0;
	else if (mwrite(put_string, sizeof(char), string_length, mfile_ptr) ==
		((int) string_length))
		return_value = string_length;

	return(return_value);
}
/* *********************************************************************** */

