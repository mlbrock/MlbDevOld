/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Re-maps a memory-mapped file.

	Revision History	:	1995-03-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <errno.h>
#include <limits.h>
#include <memory.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

#include <sys/stat.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mremap

   SYNOPSIS    :  return_code = mremap(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Re-maps a memory-mapped file to the current file size as
						determined by the ``fstat()`` function call.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mremap_basic_1
						mremap_basic_2

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mremap
						Memory-mapped File Functions:Re-map Functions:mremap
						MFILE Functions:mremap

	PUBLISH XREF:	mremap

	PUBLISH NAME:	mremap

	ENTRY CLASS	:	Memory-mapped File Functions:Re-map Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mremap(MFILE *mfile_ptr)
#else
int mremap(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int         return_code;
	struct stat stat_data;

	if (fstat(fileno(mfile_ptr->file_ptr), &stat_data))
		return_code = -1;
	else if ((return_code = mremap_basic_1(mfile_ptr, 0,
		((unsigned long) stat_data.st_size))) == 0)
		mfile_ptr->file_size = stat_data.st_size;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mremap_basic_1

   SYNOPSIS    :  return_code = mremap_basic_1(mfile_ptr, offset, length);

						int            return_code;

						MFILE         *mfile_ptr;

						unsigned long  offset;

						unsigned long  length;

   DESCRIPTION :  Re-maps a memory-mapped file to the specified length at the
						specified offset.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``offset`` is the offset within the memory-mapped file
						at which the mapping is to begin. This value should be an
						integral multiple of the system page size as returned by
						the function ``getpagesize()``.

						(.) ``length`` is the length for which the mapping is to
						be performed.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mremap
						mremap_basic_2

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mremap_basic_1
						Memory-mapped File Functions:Re-map Functions:mremap_basic_1
						MFILE Functions:mremap_basic_1

	PUBLISH XREF:	mremap_basic_1

	PUBLISH NAME:	mremap_basic_1

	ENTRY CLASS	:	Memory-mapped File Functions:Re-map Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mremap_basic_1(MFILE *mfile_ptr, unsigned long offset, unsigned long length)
#else
int mremap_basic_1(mfile_ptr, offset, length)
MFILE         *mfile_ptr;
unsigned long  offset;
unsigned long  length;
#endif /* #ifndef NARGS */
{
	int return_code;
	int fatal_error_flag;

	if (((return_code = mremap_basic_2(fileno(mfile_ptr->file_ptr),
		&mfile_ptr->mmap_size, &mfile_ptr->mmap_ptr, &mfile_ptr->current_offset,
		mfile_ptr->mmap_prot, mfile_ptr->mmap_flags, offset, length,
		&fatal_error_flag)) != 0) && fatal_error_flag)
		mclose(mfile_ptr);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mremap_basic_2

   SYNOPSIS    :  return_code = mremap_basic_2(file_handle, mmap_size,
							mmap_ptr, current_offset, mmap_prot, mmap_flags, offset,
							length, fatal_error_flag);

						int             return_code;

						int             file_handle;

						unsigned long  *mmap_size;

						volatile void **mmap_ptr;

						unsigned long  *current_offset;

						int             mmap_prot;

						int             mmap_flags;

						unsigned long   offset;

						unsigned long   length;

						int            *fatal_error_flag;

   DESCRIPTION :  Re-maps a memory-mapped file to the specified length at the
						specified offset.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``file_handle`` is file descriptor of the already opened
						file for which the mapping is to be performed.

						(.) ``mmap_size`` points to an ``unsigned long`` which
						contains the current size of any extant mapping.

						(-) If no mapping is extant at the time this function is
						invoked, the value to which ``mmap_size`` points should be
						equal to ''0''.

						(-) If this function successfully re-maps the file, the
						value to which ``mmap_size`` points will be set to the
						size of the new mapping.

						(.) ``mmap_ptr`` is a pointer to the pointer which gives
						the beginning of any extant mapping within the process
						address space.

						(-) If no mapping is extant at the time this function is
						invoked, the value to which ``mmap_ptr`` points should be
						equal to ''NULL''.

						(-) If this function successfully re-maps the file, the
						value to which ``mmap_ptr`` points will be set to the
						beginning of the new mapping.

						(.) ``current_offset`` points to an ``unsigned long``
						which contains the current position (or offset) within the
						memory-mapped file.

						(-) If ``current_offset`` is ''NULL'', no attempt will be
						made to de-reference it.

						(-) If ``current_offset`` is not ''NULL'', and the result
						of re-mapping the memory-mapped file is to place that offset
						beyond the end of the mapped area, the ``unsigned long`` to
						which ``current_offset`` points will be changed.

						(.) ``mmap_prot`` contains the ``mmap()`` protection flags
						to be used to re-map the file (the manifest constants
						''PROT_READ'' and ''PROT_WRITE'' are examples of these
						flags).

						(.) ``mmap_flags`` contains the ``mmap()`` access flags to
						be used to re-map the file (the manifest constants
						''MAP_SHARED'' and ''MAP_PRIVATE'' are examples of these
						flags).

						(.) ``offset`` is the offset within the memory-mapped file
						at which the mapping is to begin. This value should be an
						integral multiple of the system page size as returned by
						the function ``getpagesize()``.

						(.) ``length`` is the length for which the mapping is to
						be performed.

						(.) ``fatal_error_flag`` points to an integer which will
						be set to a non-zero value if this function encounters an
						consistency error. This can occur in the following
						circumstances:

						(-) Because the total sizes of an extant mapping, the new
						desired mapping, and any other mappings resulting from
						program operation may exceed the maximum allowable,
						(``2 ^ 31 - 1``) this function first un-maps any extant
						mapping, then attempts to re-map the file to the new
						specified size.

						(-) If any part of the operation of this function fails,
						the function will attempt to restore the previous mapping
						before returning.

						(-) If, however, the previous mapping cannot be restored,
						the function sets the integer to which ``fatal_error_flag``
						to an non-zero value.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  To determine appropriate values for the ``mmap_prot`` and
						``mmap_flags`` parameters, see the ''mmap(2)'' man page.

   CAVEATS     : 	
 
   SEE ALSO    :  mremap
						mremap_basic_1

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mremap_basic_2
						Memory-mapped File Functions:Re-map Functions:mremap_basic_2
						MFILE Functions:mremap_basic_2

	PUBLISH XREF:	mremap_basic_2

	PUBLISH NAME:	mremap_basic_2

	ENTRY CLASS	:	Memory-mapped File Functions:Re-map Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int mremap_basic_2(int file_handle, unsigned long *mmap_size,
	volatile void **mmap_ptr, unsigned long *current_offset, int mmap_prot,
	int mmap_flags, unsigned long offset, unsigned long length,
	int *fatal_error_flag)
#else
int mremap_basic_2(file_handle, mmap_size, mmap_ptr, current_offset,
	mmap_prot, mmap_flags, offset, length, fatal_error_flag)
int             file_handle;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   offset;
unsigned long   length;
int            *fatal_error_flag;
#endif /* #ifndef NARGS */
{
	int            return_code   = 0;
	void          *tmp_mmap_ptr  = NULL;
	unsigned long  old_mmap_size = 0;
	void          *old_mmap_ptr  = NULL;

	*fatal_error_flag = 0;

	if ((offset > ((unsigned long) LONG_MAX)) ||
		 (length > ((unsigned long) LONG_MAX))) {
		errno       = EFBIG;
		return_code = -1;
		goto EXIT_FUNCTION;
	}

	if (*mmap_ptr != NULL) {
		old_mmap_size = *mmap_size;
		old_mmap_ptr  = ((void *) *mmap_ptr);
		MFILE_munmap(old_mmap_ptr, old_mmap_size);
	}

	*mmap_size = 0;
	*mmap_ptr  = NULL;

	if (length) {
		if (((int) (tmp_mmap_ptr = ((void *) MFILE_mmap(old_mmap_ptr,
			length, mmap_prot, mmap_flags, file_handle, offset)))) != -1) {
			*mmap_size = length;
			*mmap_ptr  = ((volatile void *) tmp_mmap_ptr);
			if (current_offset != NULL)
				*current_offset = (*current_offset > length) ? length :
					*current_offset;
		}
		else {
			if (((int) (old_mmap_ptr = ((void *) MFILE_mmap(old_mmap_ptr,
				old_mmap_size, mmap_prot, mmap_flags, file_handle, 0)))) == -1)
				*fatal_error_flag = 1;
			else {
				*mmap_size = old_mmap_size;
				*mmap_ptr  = old_mmap_ptr;
			}
			return_code  = -1;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int mremap_basic_2(int file_handle, unsigned long *mmap_size,
	volatile void **mmap_ptr, unsigned long *current_offset, int mmap_prot,
	int mmap_flags, unsigned long offset, unsigned long length,
	int *fatal_error_flag)
#else
int mremap_basic_2(file_handle, mmap_size, mmap_ptr, current_offset,
	mmap_prot, mmap_flags, offset, length, fatal_error_flag)
int             file_handle;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   offset;
unsigned long   length;
int            *fatal_error_flag;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	*fatal_error_flag = 0;

	if ((offset > ((unsigned long) LONG_MAX)) ||
		 (length > ((unsigned long) LONG_MAX))) {
		errno       = EFBIG;
		return_code = -1;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

#ifdef TEST_MAIN

#define TEST_FILE								"ERASE.ME3"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code   = 0;
	MFILE          *mfile_ptr     = NULL;
	unsigned long   old_file_size = ULONG_MAX;

	fprintf(stderr, "Text routine for function 'mremap()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------\n\n");

	if ((mfile_ptr = mopen(TEST_FILE, "r")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open input file '%s'.\n\n",
			TEST_FILE);
		return_code = -1;
	}
	else {
		while (!return_code) {
			if (mremap(mfile_ptr)) {
				fprintf(stderr, "ERROR: %s '%s'.\n\n",
					"Unable to 'mremap()' file", TEST_FILE);
				return_code = -1;
				break;
			}
			if (mfile_ptr->file_size != old_file_size) {
				fprintf(stderr, "File '%s' size: %10lu\n", TEST_FILE,
					mfile_ptr->file_size);
				old_file_size = mfile_ptr->file_size;
			}
			SDTIF_sleep(1);
		}
		mclose(mfile_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

