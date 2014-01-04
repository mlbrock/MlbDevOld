/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Flushes a memory-mapped file to disk.

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

   NAME        :  mflush

   SYNOPSIS    :  return_code = mflush(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Flushes the memory image of the memory-mapped file with
						its persistant store on disk if the file has been opened
						for writing.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if the memory-mapped file was opened for
						writing.

						(.) The value of the manifest constant ''EOF'' if an
						error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fflush()``.

   CAVEATS     :  

   SEE ALSO    :  mflushall
						mflush_async

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mflush
						Memory-mapped File Functions:Flush Functions:mflush
						MFILE Functions:mflush

	PUBLISH XREF:	mflush

	PUBLISH NAME:	mflush

	ENTRY CLASS	:	Memory-mapped File Functions:Flush Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mflush(MFILE *mfile_ptr)
#else
int mflush(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = EOF;

   if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		if (mfile_ptr->mfile_flags & MFILE_MODE_WRITE)
#ifndef MFILE_MMAP_NON_NATIVE
			MFILE_msync(mfile_ptr->mmap_ptr, mfile_ptr->file_size, 0);
#else
			fflush(mfile_ptr->file_ptr);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
		return_code = 0;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mflushall

   SYNOPSIS    :  flushed_mfile_count = mflushall();

						int flushed_mfile_count;

   DESCRIPTION :  Flushes the memory image of all memory-mapped files which
						have been opened for writing with their persistent store on
						disk.

   PARAMETERS  :  None.

   RETURNS     :  The number of memory-mapped files flushed.

   NOTES       :  This function is the memory-mapped file library analogue of
						the UNIX library function ``flushall()``.

   CAVEATS     :  

   SEE ALSO    :  mflush
						mflush_async

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mflushall
						Memory-mapped File Functions:Flush Functions:mflushall
						MFILE Functions:mflushall

	PUBLISH XREF:	mflushall

	PUBLISH NAME:	mflushall

	ENTRY CLASS	:	Memory-mapped File Functions:Flush Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mflushall(void)
#else
int mflushall()
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	int          flushed_count = 0;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE) {
			if (MFILE_EntryList[count_1].mfile_flags & MFILE_MODE_WRITE)
				mflush(MFILE_EntryList + count_1);
			flushed_count++;
		}
	}

	return(flushed_count);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mflush_async

   SYNOPSIS    :  return_code = mflush_async(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

						int    async_flag;

   DESCRIPTION :  Flushes the memory image of the memory-mapped file with
						its persistant store on disk if the file has been opened
						for writing.

						The memory-mapped file may be flushed asynchronously to
						program operation if specified by the caller of the function
						and if supported by the underlying implementation. If so,
						the function will return immediately once it has requested
						that the operating system schedule the write operations.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``async_flag`` indicates whether the memory-mapped
						file is to be flushed asynchronously.

						(..) Set the ``async_flag`` parameter to a non-zero value
						if you want this function to flush the memory-mapped file
						asynchronously.

						(.) For normal (that is, synchronous flushing of the
						memory-mapped file, set the ``async_flag`` parameter to
						zero.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if the memory-mapped file was opened for
						writing.

						(.) The value of the manifest constant ''EOF'' if an
						error occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mflush
						mflushall

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mflush_async
						Memory-mapped File Functions:Flush Functions:mflush_async
						MFILE Functions:mflush_async

	PUBLISH XREF:	mflush_async

	PUBLISH NAME:	mflush_async

	ENTRY CLASS	:	Memory-mapped File Functions:Flush Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mflush_async(MFILE *mfile_ptr, int async_flag)
#else
int mflush_async(mfile_ptr, async_flag)
MFILE *mfile_ptr;
int    async_flag;
#endif /* #ifndef NARGS */
{
	int return_code = EOF;

   if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		if (mfile_ptr->mfile_flags & MFILE_MODE_WRITE) {
#ifndef MFILE_MMAP_NON_NATIVE
			MFILE_msync(mfile_ptr->mmap_ptr, mfile_ptr->file_size,
				(async_flag) ? MS_ASYNC : MS_SYNC);
#else
			return_code = async_flag;		/*	To avoid Lint-like complaints.	*/
			fflush(mfile_ptr->file_ptr);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
		}
		return_code = 0;
	}

	return(return_code);
}
/* *********************************************************************** */


