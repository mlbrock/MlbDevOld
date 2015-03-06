/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Rewinds the current offset of a memory-mapped file
								to the beginning of the file.

	Revision History	:	1992-08-25 --- Creation.
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

   NAME        :  mrewind

   SYNOPSIS    :  mrewind(mfile_ptr);

						MFILE *mfile_ptr;

   DESCRIPTION :  Sets the "current" position in a memory-mapped file to
						the first byte of the file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Void.

   NOTES       :  This function is equivalent to the following code:

						(-)mseek(mfile_ptr, 0L, SEEK_SET);

						This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``rewind``.

   CAVEATS     :  

   SEE ALSO    :  mseek

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	mrewind
						Memory-mapped File Functions:mrewind
						MFILE Functions:mrewind

	PUBLISH XREF:	mrewind

	PUBLISH NAME:	mrewind

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void mrewind(MFILE *mfile_ptr)
#else
void mrewind(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	mseek(mfile_ptr, 0L, SEEK_SET);
}
/* *********************************************************************** */

