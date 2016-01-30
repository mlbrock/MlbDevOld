/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Moves the current offset within a memory-mapped file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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

   NAME        :  mseek

   SYNOPSIS    :  return_code = mseek(mfile_ptr, offset, position_type);

						int    return_code;

						MFILE *mfile_ptr;

						off_t  offset;

						int    position_type;

   DESCRIPTION :  Changes the "current" position in memory-mapped file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``offset`` is the number of bytes relative to the
						``position_type`` parameter to which the "current" position
						of the memory-mapped file is to be changed.

						(.) ``position_type`` indicates the logical file location
						relative to which the "current" position of the
						memory-mapped file is to be changed. It takes one of the
						following values:

						(..) The manifest constant ''SEEK_SET'', which indicates
						that file positioning is to performed relative to the
						beginning of the memory-mapped file.

						(..) The manifest constant ''SEEK_CUR'', which indicates
						that file positioning is to performed relative to the
						current position within the memory-mapped file.

						(..) The manifest constant ''SEEK_END'', which indicates
						that file positioning is to performed relative to the
						end of the memory-mapped file.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fseek()``.

   CAVEATS     :  

   SEE ALSO    :  mtell

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	mseek
						Memory-mapped File Functions:mseek
						MFILE Functions:mseek

	PUBLISH XREF:	mseek

	PUBLISH NAME:	mseek

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int mseek(MFILE *mfile_ptr, long offset, int position_type)
#else
int mseek(mfile_ptr, offset, position_type)
MFILE *mfile_ptr;
off_t  offset;
int    position_type;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MFILE_ValidateMFILEPtr(mfile_ptr)) == 0) {
		switch (position_type) {
			case	SEEK_SET	:
				if ((offset > -1) && (offset <= mfile_ptr->file_size))
					mfile_ptr->current_offset = offset;
				else
					return_code = -1;
				break;
			case	SEEK_CUR	:
				offset = ((long) mfile_ptr->current_offset) + offset;
				if ((offset > -1) && (offset <= mfile_ptr->file_size))
					mfile_ptr->current_offset = offset;
				else
					return_code = -1;
				break;
			case	SEEK_END	:
				if ((offset > -1) && (offset <= mfile_ptr->file_size))
					mfile_ptr->current_offset = mfile_ptr->file_size - offset;
				else
					return_code = -1;
				break;
			default			:
				return_code = -1;
				break;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int mseek(MFILE *mfile_ptr, long offset, int position_type)
#else
int mseek(mfile_ptr, offset, position_type)
MFILE *mfile_ptr;
long   offset;
int    position_type;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MFILE_ValidateMFILEPtr(mfile_ptr)) == 0) {
		fseek(mfile_ptr->file_ptr, offset, position_type);
		mfile_ptr->current_offset = ((long) ftell(mfile_ptr->file_ptr));
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

