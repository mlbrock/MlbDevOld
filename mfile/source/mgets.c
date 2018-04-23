/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a string from a memory-mapped file.

	Revision History	:	1992-09-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

   NAME        :  mgets

   SYNOPSIS    :  string_ptr = mgets(buffer_ptr, buffer_max, mfile_ptr);

						char  *string_ptr;

						char  *buffer_ptr;

						int    buffer_max;

						MFILE *mfile_ptr;

   DESCRIPTION :  Returns the next string in the specified memory-mapped
						file. The function stops reading characters into the
						string ``buffer_ptr`` when it has read ``buffer_max``
						characters or a new-line character (ASCII 10), whichever
						comes first.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``buffer_ptr`` points to the string into which the
						characters from the memory-mapped file are to be placed.

						(.) ``buffer_max`` is the maximum length of the string
						``buffer_ptr`` to be used by this function. No more than
						``buffer_max - 1`` characters will be copied into the string
						(one byte is reserved for the placement of the null byte).

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) ``buffer_ptr`` if no error occurred.

						(.) ''NULL'' if the end of the memory-mapped file has been
						reached or if an error occurs.

   NOTES       :  If this function returns because a new-line character was
						encountered, that character will be included in the string
						returned by the function.

						All strings returned by this function will have an ASCII 0
						appended at the end of the string.

   					This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fgets()``.

   CAVEATS     :  

   SEE ALSO    :  mputs

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	mgets
						Memory-mapped File Functions:mgets
						MFILE Functions:mgets

	PUBLISH XREF:	mgets

	PUBLISH NAME:	mgets

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
char *mgets(char *buffer_ptr, int buffer_max, MFILE *mfile_ptr)
#else
char *mgets(buffer_ptr, buffer_max, mfile_ptr)
char  *buffer_ptr;
int    buffer_max;
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	char *return_ptr = buffer_ptr;

	if ((!(mfile_ptr->mfile_flags & MFILE_MODE_READ)) ||
		(mfile_ptr->current_offset >= mfile_ptr->file_size))
		return_ptr = NULL;
	else {
		while ((buffer_max > 0) &&
			(mfile_ptr->current_offset < mfile_ptr->file_size)) {
			buffer_max--;
			*buffer_ptr = *(((char *) mfile_ptr->mmap_ptr) +
				mfile_ptr->current_offset++);
			if (*buffer_ptr++ == '\n')
				break;
		}
		*buffer_ptr = '\0';
	}

	return(return_ptr);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
char *mgets(char *buffer_ptr, int buffer_max, MFILE *mfile_ptr)
#else
char *mgets(buffer_ptr, buffer_max, mfile_ptr)
char  *buffer_ptr;
int    buffer_max;
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	char *return_ptr = buffer_ptr;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_READ))
		return_ptr = NULL;
	else {
		fgets(buffer_ptr, buffer_max, mfile_ptr->file_ptr);
		mfile_ptr->current_offset = ((unsigned long) ftell(mfile_ptr->file_ptr));
	}

	return(return_ptr);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

