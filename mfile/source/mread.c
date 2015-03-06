/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads blocks from a memory-mapped file.

	Revision History	:	1992-03-21 --- Creation.
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

#include <memory.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mread

   SYNOPSIS    :  element_count = mread(data_ptr, element_size, element_count,
							mfile_ptr);

						int           element_count;

						void         *data_ptr;

						unsigned int  element_size;

						unsigned int  element_count;

						MFILE        *mfile_ptr;

   DESCRIPTION :  Copies ``element_count`` blocks of size ``element_size``
						from the memory-mapped file specified by ``mfile_ptr``
						into the area of memory to which ``data_ptr`` points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_ptr`` points to the area of memory into which the
						data copied from the memory-mapped file is to be placed. It
						should be at least ``element_count * element_size`` bytes
						in length.

						(.) ``element_size`` is the size of each of the blocks to be
						copied from the memory-mapped file.

						(.) ``element_count`` is the number of blocks to be copied
						from the memory-mapped file.

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  The number of complete blocks copied from the memory-mapped
						file.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fread()``.

   CAVEATS     :  

   SEE ALSO    :  mwrite

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mread
						Memory-mapped File Functions:mread
						MFILE Functions:mread

	PUBLISH XREF:	mread

	PUBLISH NAME:	mread

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int mread(void *data_ptr, unsigned int element_size, unsigned int element_count,
	MFILE *mfile_ptr)
#else
int mread(data_ptr, element_size, element_count, mfile_ptr)
void         *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
#endif /* #ifndef NARGS */
{
	if (!(mfile_ptr->mfile_flags & MFILE_MODE_READ))
		element_count = 0;
	else if ((mfile_ptr->current_offset + (element_size * element_count)) >
		mfile_ptr->file_size) {
		memcpy(data_ptr, ((char *) mfile_ptr->mmap_ptr) +
			mfile_ptr->current_offset,
			mfile_ptr->file_size - mfile_ptr->current_offset);
		element_count              =
			(mfile_ptr->file_size - mfile_ptr->current_offset) / element_size;
		mfile_ptr->current_offset  = mfile_ptr->file_size;
		mfile_ptr->mfile_flags    |= MFILE_FLAG_READ;
	}
	else {
		memcpy(data_ptr, ((char *) mfile_ptr->mmap_ptr) +
			mfile_ptr->current_offset, element_size * element_count);
		mfile_ptr->current_offset += element_size * element_count;
		mfile_ptr->mfile_flags    |= MFILE_FLAG_READ;
	}

	return(element_count);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int mread(void *data_ptr, unsigned int element_size, unsigned int element_count,
	MFILE *mfile_ptr)
#else
int mread(data_ptr, element_size, element_count, mfile_ptr)
void         *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
#endif /* #ifndef NARGS */
{
	if (!(mfile_ptr->mfile_flags & MFILE_MODE_READ))
		element_count = 0;
	else {
		element_count = fread(data_ptr, element_size, element_count,
			mfile_ptr->file_ptr);
		mfile_ptr->current_offset += element_size * element_count;
		mfile_ptr->mfile_flags    |= MFILE_FLAG_READ;
	}

	return(element_count);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

