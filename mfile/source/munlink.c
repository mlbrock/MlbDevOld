/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes and unlinks a memory-mapped file.

	Revision History	:	1994-07-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

   NAME        :  munlink

   SYNOPSIS    :  return_code = munlink(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Closes a file which was opened by a call to ``mopen`` or
						``mtmpfile`` and unlinks that file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mopen
						mclose
						mtmpfile

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	munlink
						Memory-mapped File Functions:Close Functions:munlink
						MFILE Functions:munlink

	PUBLISH XREF:	munlink

	PUBLISH NAME:	munlink

	ENTRY CLASS	:	Memory-mapped File Functions:Close Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int munlink(MFILE *mfile_ptr)
#else
int munlink(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
#ifndef MFILE_MMAP_NON_NATIVE
		if (mfile_ptr->mmap_ptr)
			MFILE_munmap(mfile_ptr->mmap_ptr, mfile_ptr->mmap_size);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
		fclose(mfile_ptr->file_ptr);
		unlink(mfile_ptr->file_name);
		free(mfile_ptr->file_name);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}
/* *********************************************************************** */

