/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets the flags for a memory-mapped file.

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

   NAME        :  msetflag

   SYNOPSIS    :  return_code = msetflag(mfile_ptr, mmap_prot, mmap_flags);

						int    return_code;

						MFILE *mfile_ptr;

						int    mmap_prot;

						int    mmap_flags;

   DESCRIPTION :  Re-mmaps a memory-mapped file using the flags specified by
						parameters ``mmap_prot`` and ``mmap_flags``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``mmap_prot`` contains the ``mmap()`` protection flags
						to be used to re-mmap the file (the manifest constants
						''PROT_READ'' and ''PROT_WRITE'' are examples of these
						flags).

						(.) ``mmap_flags`` contains the ``mmap()`` access flags to
						be used to re-mmap the file (the manifest constants
						''MAP_SHARED'' and ''MAP_PRIVATE'' are examples of these
						flags).

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  To determine appropriate values for the ``mmap_prot`` and
						``mmap_flags`` parameters, see the ''mmap(2)'' man page.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	msetflag
						Memory-mapped File Functions:msetflag
						MFILE Functions:msetflag

	PUBLISH XREF:	msetflag

	PUBLISH NAME:	msetflag

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int msetflag(MFILE *mfile_ptr, int mmap_prot, int mmap_flags)
#else
int msetflag(mfile_ptr, mmap_prot, mmap_flags)
MFILE *mfile_ptr;
int    mmap_prot;
int    mmap_flags;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if ((mfile_ptr->mmap_prot != mmap_prot) ||
		(mfile_ptr->mmap_flags != mmap_flags)) {
		mfile_ptr->mmap_prot  = mmap_prot;
		mfile_ptr->mmap_flags = mmap_flags;
		if (mfile_ptr->mmap_ptr) {
			MFILE_munmap(mfile_ptr->mmap_ptr, mfile_ptr->mmap_size);
			mfile_ptr->mmap_ptr = NULL;
			if (((int) (mfile_ptr->mmap_ptr = ((char *) MFILE_mmap(NULL,
				mfile_ptr->mmap_size, mfile_ptr->mmap_prot,
				mfile_ptr->mmap_flags, fileno(mfile_ptr->file_ptr), 0)))) == -1) {
				mclose(mfile_ptr);
				return_code = -1;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int msetflag(MFILE *mfile_ptr, int mmap_prot, int mmap_flags)
#else
int msetflag(mfile_ptr, mmap_prot, mmap_flags)
MFILE *mfile_ptr;
int    mmap_prot;
int    mmap_flags;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if ((mfile_ptr->mmap_prot != mmap_prot) ||
		(mfile_ptr->mmap_flags != mmap_flags)) {
		mfile_ptr->mmap_prot  = mmap_prot;
		mfile_ptr->mmap_flags = mmap_flags;
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

