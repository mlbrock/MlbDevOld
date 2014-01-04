/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets the logical buffer size of a memory-mapped file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
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

   NAME        :  msetbuf

   SYNOPSIS    :  msetbuf(mfile_ptr, buffer_size);

						MFILE        *mfile_ptr;

						unsigned int  buffer_size;

   DESCRIPTION :  Sets write pre-allocation for a memory-mapped file. If set
						to a value greater than zero, than the library will
						allocate additional chunks to the memory-mapped file in
						sizes no smaller than that value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``buffer_size`` is the size of write pre-allocation to
						be set for the memory-mapped file.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	msetbuf
						Memory-mapped File Functions:msetbuf
						MFILE Functions:msetbuf

	PUBLISH XREF:	msetbuf

	PUBLISH NAME:	msetbuf

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
void msetbuf(MFILE *mfile_ptr, unsigned int buffer_size)
#else
void msetbuf(mfile_ptr, buffer_size)
MFILE        *mfile_ptr;
unsigned int  buffer_size;
#endif /* #ifndef NARGS */
{
	mfile_ptr->buffer_size = buffer_size;
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
void msetbuf(MFILE *mfile_ptr, unsigned int buffer_size)
#else
void msetbuf(mfile_ptr, buffer_size)
MFILE        *mfile_ptr;
unsigned int  buffer_size;
#endif /* #ifndef NARGS */
{
	if (!setvbuf(mfile_ptr->file_ptr, NULL, _IOFBF, buffer_size))
		mfile_ptr->buffer_size = buffer_size;
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

