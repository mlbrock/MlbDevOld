/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes a memory-mapped file.

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

#include <memory.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Some external variables needed by this function . . .						*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mclose

   SYNOPSIS    :  return_code = mclose(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Closes a file which was opened by a call to ``mopen``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fclose``.

   CAVEATS     :  

   SEE ALSO    :  mopen
						mcloseall
						mclose_no_unmap
						mclose_to_offset

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	mclose
						Memory-mapped File Functions:Close Functions:mclose
						MFILE Functions:mclose

	PUBLISH XREF:	mclose

	PUBLISH NAME:	mclose

	ENTRY CLASS	:	Memory-mapped File Functions:Close Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mclose(MFILE *mfile_ptr)
#else
int mclose(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
#ifndef MFILE_MMAP_NON_NATIVE
		if ((mfile_ptr->mmap_ptr) && mfile_ptr->file_size &&
			(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
			MFILE_msync(mfile_ptr->mmap_ptr, mfile_ptr->file_size, 0);
		if (mfile_ptr->mmap_ptr)
			MFILE_munmap(mfile_ptr->mmap_ptr, mfile_ptr->mmap_size);
		if (mfile_ptr->mfile_flags & MFILE_MODE_WRITE)
			ftruncate(fileno(mfile_ptr->file_ptr), mfile_ptr->file_size);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
		free(mfile_ptr->file_name);
		fclose(mfile_ptr->file_ptr);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mcloseall

   SYNOPSIS    :  closed_mfile_count = mcloseall();

						int    closed_mfile_count;

   DESCRIPTION :  Closes all open memory-mapped files.

   PARAMETERS  :  None.

   RETURNS     :  The number of memory-mapped files closed.

   NOTES       :  This function is the memory-mapped file library analogue of
						the UNIX library function ``fcloseall``.

   CAVEATS     :  

   SEE ALSO    :  mclose

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	mcloseall
						Memory-mapped File Functions:Close Functions:mcloseall
						MFILE Functions:mcloseall

	PUBLISH XREF:	mcloseall

	PUBLISH NAME:	mcloseall

	ENTRY CLASS	:	Memory-mapped File Functions:Close Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mcloseall(void)
#else
int mcloseall()
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	int          closed_count = 0;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE) {
			mclose(MFILE_EntryList + count_1);
			closed_count++;
		}
	}

	return(closed_count);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mclose_no_unmap

   SYNOPSIS    :  return_code = mclose_no_unmap(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Closes a file which was opened by a call to ``mopen``.

						This function is distinguished from ``mclose`` by virtue
						of the fact that it does not do any of the following logic:

						(.) synchronize the memory-mapped data with its associated
						file;

						(.) un-map the memory for its associated file; or,

						(.) truncate the file to the length specified by the
						``file_size`` member of the structure ''MFILE''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :  mclose

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	mclose_no_unmap
						Memory-mapped File Functions:Close Functions:mclose_no_unmap
						MFILE Functions:mclose_no_unmap

	PUBLISH XREF:	mclose_no_unmap

	PUBLISH NAME:	mclose_no_unmap

	ENTRY CLASS	:	Memory-mapped File Functions:Close Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mclose_no_unmap(MFILE *mfile_ptr)
#else
int mclose_no_unmap(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		free(mfile_ptr->file_name);
		fclose(mfile_ptr->file_ptr);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mclose_to_offset

   SYNOPSIS    :  return_code = mclose_to_offset(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Closes a file which was opened by a call to ``mopen``.

						This function is distinguished from ``mclose`` by virtue
						of the fact that memory-mapped files opened for writing are
						truncated to the current file offset, ''NOT'' the current
						file size.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :	If the memory-mapped file was not opened for writing, or
						if the current offset into the file is equal to the file
						size, this function performs in the same fashion as the
						function ``mclose``.

   CAVEATS     :  

   SEE ALSO    :  mclose

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	mclose_to_offset
						Memory-mapped File Functions:Close Functions:mclose_to_offset
						MFILE Functions:mclose_to_offset

	PUBLISH XREF:	mclose_to_offset

	PUBLISH NAME:	mclose_to_offset

	ENTRY CLASS	:	Memory-mapped File Functions:Close Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mclose_to_offset(MFILE *mfile_ptr)
#else
int mclose_to_offset(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	if ((mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
		mfile_ptr->file_size = mfile_ptr->current_offset;

	return(mclose(mfile_ptr));
}
/* *********************************************************************** */

