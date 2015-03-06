/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a single character from a memory-mapped file.

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

   NAME        :  mgetc

   SYNOPSIS    :  return_char = mgetc(mfile_ptr);

						int    return_char;

						MFILE *mfile_ptr;

   DESCRIPTION :  Returns the next character in the specified memory-mapped
						file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) The character read (after conversion to an integer
						without sign-extension) if successful.

						(.) The value of the manifest constant ''EOF'' if
						the end of the memory-mapped file has been reached or if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fgetc()``.

   CAVEATS     :  

   SEE ALSO    :  mputc

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mgetc
						Memory-mapped File Functions:mgetc
						MFILE Functions:mgetc

	PUBLISH XREF:	mgetc

	PUBLISH NAME:	mgetc

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mgetc(MFILE *mfile_ptr)
#else
int mgetc(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_char = EOF;

	if ((mfile_ptr->mfile_flags & MFILE_MODE_READ) &&
		(mfile_ptr->current_offset < mfile_ptr->file_size)) {
#ifndef MFILE_MMAP_NON_NATIVE
		return_char = ((int) *(((char *) mfile_ptr->mmap_ptr) +
			mfile_ptr->current_offset++));
#else
		return_char = fgetc(mfile_ptr->file_ptr);
		mfile_ptr->current_offset = ((unsigned long) ftell(mfile_ptr->file_ptr));
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
	}

	return(return_char);
}
/* *********************************************************************** */

