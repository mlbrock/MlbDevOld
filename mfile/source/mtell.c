/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the current offset within a memory-mapped
								file.

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

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtell

   SYNOPSIS    :  current_offset = mtell(mfile_ptr);

						off_t  current_offset;

						MFILE *mfile_ptr;

   DESCRIPTION :  Returns the "current" position in memory-mapped file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) The current position in the memory-mapped file if
						successful.

						(.) ''-1L'' if an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``ftell()``.

   CAVEATS     :  

   SEE ALSO    :  mseek

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mtell
						Memory-mapped File Functions:mtell
						MFILE Functions:mtell

	PUBLISH XREF:	mtell

	PUBLISH NAME:	mtell

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
off_t mtell(MFILE *mfile_ptr)
#else
off_t mtell(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return((!MFILE_ValidateMFILEPtr(mfile_ptr)) ? mfile_ptr->current_offset :
		((off_t) -1L));
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
off_t mtell(MFILE *mfile_ptr)
#else
long mtell(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return((!MFILE_ValidateMFILEPtr(mfile_ptr)) ?
		((long) ftell(mfile_ptr->file_ptr)) : -1L);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

