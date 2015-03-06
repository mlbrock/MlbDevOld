/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Puts a single character into a memory-mapped file.

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

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mputc

   SYNOPSIS    :  return_code = mputc(put_char, mfile_ptr);

						int    return_code;

						int    put_char;

						MFILE *mfile_ptr;

   DESCRIPTION :  Places a character into a memory-mapped file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``put_char`` is the character to be placed into the
						memory-mapped file.

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) The character placed into the memory-mapped file if
						successful.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fputc()``.

   CAVEATS     :  

   SEE ALSO    :  mgetc

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mputc
						Memory-mapped File Functions:mputc
						MFILE Functions:mputc

	PUBLISH XREF:	mputc

	PUBLISH NAME:	mputc

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mputc(int put_char, MFILE *mfile_ptr)
#else
int mputc(put_char, mfile_ptr)
int    put_char;
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int  return_value = EOF;
	char tmp_char     = ((char) put_char);

	if (mwrite(&tmp_char, sizeof(char), 1, mfile_ptr) == 1)
		return_value = put_char;

	return(return_value);
}
/* *********************************************************************** */

