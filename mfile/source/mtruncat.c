/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Truncates a memory-mapped file.

	Revision History	:	1995-03-05 --- Creation.
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

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtruncate

   SYNOPSIS    :  return_code = mtruncate(mfile_ptr, length);

						int            return_code;

						MFILE         *mfile_ptr;

						unsigned long  length;

   DESCRIPTION :  Truncates a memory-mapped file to specified length.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``length`` is the length to which the memory-mapped
						file is to be truncated.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  This function is the memory-mapped file library analogue of
						the UNIX library function ``ftruncate()``.

   CAVEATS     :  This function relies upon the underlying semantics of the
						``ftruncate`` system call. If it is possible for
						``ftruncate`` to return successfully without having
						actually allocated file-system blocks to the file, then
						``holes`` may be left in portions of the file. The operating
						system will attempt to fill-in these holes by allocating
						blocks to the file as those portions are accessed --- so
						long as space remains available on the device.

						If the device should happen to become full, it is possible
						for an access through the memory-mapped pointer to a portion
						of the file corresponding to a ``hole`` to fail. In this
						case you'll encounter a ''SIGBUS'' error.

						Similar situations can occur where file-system quotas are
						exceeded by the program.

						To avoid these potential problems, it's best if you call
						the function ``mtruncate_safe`` instead. ``mtruncate_safe``
						forces the operating system to allocate file-system blocks
						to the file.

   SEE ALSO    :  mtruncate_safe
						mtruncate_basic_1
						mtruncate_basic_2

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mtruncate
						Memory-mapped File Functions:Truncate Functions:mtruncate
						MFILE Functions:mtruncate

	PUBLISH XREF:	mtruncate

	PUBLISH NAME:	mtruncate

	ENTRY CLASS	:	Memory-mapped File Functions:Truncate Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mtruncate(MFILE *mfile_ptr, unsigned long length)
#else
int mtruncate(mfile_ptr, length)
MFILE         *mfile_ptr;
unsigned long  length;
#endif /* #ifndef NARGS */
{
	return(mtruncate_basic_1(mfile_ptr, length, 0));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtruncate_safe

   SYNOPSIS    :  return_code = mtruncate_safe(mfile_ptr, length);

						int            return_code;

						MFILE         *mfile_ptr;

						unsigned long  length;

   DESCRIPTION :  Truncates a memory-mapped file to specified length.

						If the ``length`` parameter is greater than the mmap'ed
						file size at the time of the call, this function will
						attempt to force the operating system to allocate
						file-system blocks to the file.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``length`` is the length to which the memory-mapped
						file is to be truncated.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  Because this function forces the operating system to
						actually allocate file-system blocks to the file, its
						use is to be preferred over ``mtruncate``.

   CAVEATS     :  

   SEE ALSO    :  mtruncate
						mtruncate_basic_1
						mtruncate_basic_2

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mtruncate_safe
						Memory-mapped File Functions:Truncate Functions:mtruncate_safe
						MFILE Functions:mtruncate_safe

	PUBLISH XREF:	mtruncate_safe

	PUBLISH NAME:	mtruncate_safe

	ENTRY CLASS	:	Memory-mapped File Functions:Truncate Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mtruncate_safe(MFILE *mfile_ptr, unsigned long length)
#else
int mtruncate_safe(mfile_ptr, length)
MFILE         *mfile_ptr;
unsigned long  length;
#endif /* #ifndef NARGS */
{
	return(mtruncate_basic_1(mfile_ptr, length, 1));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtruncate_basic_1

   SYNOPSIS    :  return_code = mtruncate_basic_1(mfile_ptr, length,
							safe_flag);

						int            return_code;

						MFILE         *mfile_ptr;

						unsigned long  length;

						int            safe_flag;

   DESCRIPTION :  Truncates a memory-mapped file to specified length.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``length`` is the length to which the memory-mapped
						file is to be truncated.

						(.) ``safe_flag`` indicates whether the function is to
						ensure that the operating system actually allocates space
						for the new file size.

						(-) If ``safe_flag`` is ''0'', the file will be truncated
						by way of calling the function ``ftruncate()``.

						(-) If ``safe_flag`` is non-zero, and the file will be
						truncated by forcing the operating system to allocate each
						block of the file.

						(-) The ``safe_flag`` parameter has no effect unless the
						new file size is to be greater than the old file size
						(that is, the ``length`` parameter is greater than the
						value to which the ``file_size`` parameter points).

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mtruncate
						mtruncate_safe
						mtruncate_basic_2

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mtruncate_basic_1
						Memory-mapped File Functions:Truncate Functions:mtruncate_basic_1
						MFILE Functions:mtruncate_basic_1

	PUBLISH XREF:	mtruncate_basic_1

	PUBLISH NAME:	mtruncate_basic_1

	ENTRY CLASS	:	Memory-mapped File Functions:Truncate Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mtruncate_basic_1(MFILE *mfile_ptr, unsigned long length, int safe_flag)
#else
int mtruncate_basic_1(mfile_ptr, length, safe_flag)
MFILE         *mfile_ptr;
unsigned long  length;
int            safe_flag;
#endif /* #ifndef NARGS */
{
	int return_code;
	int fatal_error_flag;

#ifndef MFILE_MMAP_NON_NATIVE
#ifndef fileno
# define fileno(file_ptr)					(((file_ptr) == file_ptr) ? 0 : 1)
#endif /* #ifndef fileno */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		errno       = EACCES;
		return_code = -1;
	}
	else if (((return_code = mtruncate_basic_2(fileno(mfile_ptr->file_ptr),
		&mfile_ptr->file_size, &mfile_ptr->mmap_size, &mfile_ptr->mmap_ptr,
		&mfile_ptr->current_offset, mfile_ptr->mmap_prot, mfile_ptr->mmap_flags,
		length, safe_flag, &fatal_error_flag)) != 0) && fatal_error_flag)
		mclose(mfile_ptr);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtruncate_basic_2

   SYNOPSIS    :  return_code = mtruncate_basic_2(file_handle, file_size,
							mmap_size, mmap_ptr, current_offset, mmap_prot,
							mmap_flags, length, safe_flag, fatal_error_flag);

						int             return_code;

						int             file_handle;

						unsigned long  *file_size;

						unsigned long  *mmap_size;

						volatile void **mmap_ptr;

						unsigned long  *current_offset;

						int             mmap_prot;

						int             mmap_flags;

						unsigned long   length;

						int             safe_flag;

						int            *fatal_error_flag;

   DESCRIPTION :  Truncates a memory-mapped file to specified length.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``file_handle`` is file descriptor of the already opened
						file for which the truncation is to be performed.

						(.) ``file_size`` points to an ``unsigned long`` which
						contains the current size of the file.

						(-) If this function successfully truncates the file, the
						value to which ``file_size`` points will be set to the
						new size of the file.

						(.) ``mmap_size`` points to an ``unsigned long`` which
						contains the current size of any extant mapping.

						(-) If no mapping is extant at the time this function is
						invoked, the value to which ``mmap_size`` points should be
						equal to ''0''.

						(-) If this function successfully truncates the file, the
						value to which ``mmap_size`` points will be set to the
						size of the new mapping.

						(.) ``mmap_ptr`` is a pointer to the pointer which gives
						the beginning of any extant mapping within the process
						address space.

						(-) If no mapping is extant at the time this function is
						invoked, the value to which ``mmap_ptr`` points should be
						equal to ''NULL''.

						(-) If this function successfully truncates the file, the
						value to which ``mmap_ptr`` points will be set to the
						beginning of the new mapping.

						(.) ``current_offset`` points to an ``unsigned long``
						which contains the current position (or offset) within the
						memory-mapped file.

						(-) If ``current_offset`` is ''NULL'', no attempt will be
						made to de-reference it.

						(-) If ``current_offset`` is not ''NULL'', and the result
						of truncating the memory-mapped file is to place that offset
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

						(.) ``length`` is the length to which the memory-mapped
						file is to be truncated.

						(.) ``safe_flag`` indicates whether the function is to
						ensure that the operating system actually allocates space
						for the new file size.

						(-) If ``safe_flag`` is ''0'', the file will be truncated
						by way of calling the function ``ftruncate()``.

						(-) If ``safe_flag`` is non-zero, and the file will be
						truncated by forcing the operating system to allocate each
						block of the file.

						(-) The ``safe_flag`` parameter has no effect unless the
						new file size is to be greater than the old file size
						(that is, the ``length`` parameter is greater than the
						value to which the ``file_size`` parameter points).

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

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mtruncate
						mtruncate_safe
						mtruncate_basic_1

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	mtruncate_basic_2
						Memory-mapped File Functions:Truncate Functions:mtruncate_basic_2
						MFILE Functions:mtruncate_basic_2

	PUBLISH XREF:	mtruncate_basic_2

	PUBLISH NAME:	mtruncate_basic_2

	ENTRY CLASS	:	Memory-mapped File Functions:Truncate Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int mtruncate_basic_2(int file_handle, unsigned long *file_size,
	unsigned long *mmap_size, volatile void **mmap_ptr,
	unsigned long *current_offset, int mmap_prot, int mmap_flags,
	unsigned long length, int safe_flag, int *fatal_error_flag)
#else
int mtruncate_basic_2(file_handle, file_size, mmap_size, mmap_ptr,
	current_offset, mmap_prot, mmap_flags, length, safe_flag, fatal_error_flag)
int             file_handle;
unsigned long  *file_size;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   length;
int             safe_flag;
int            *fatal_error_flag;
#endif /* #ifndef NARGS */
{
	int            return_code            = 0;
	void          *tmp_mmap_ptr           = NULL;
	unsigned long  old_file_size          = 0;
	unsigned long  old_mmap_size          = 0;
	void          *old_mmap_ptr           = NULL;
	int            file_size_changed_flag = 0;
	unsigned long  count_1;
	unsigned int   write_length;
	char           buffer[8192];

	*fatal_error_flag = 0;

	if (length > ((unsigned long) LONG_MAX)) {
		errno       = EFBIG;
		return_code = -1;
		goto EXIT_FUNCTION;
	}

	if (*mmap_ptr != NULL) {
		old_file_size = *file_size;
		old_mmap_size = *mmap_size;
		old_mmap_ptr  = ((void *) *mmap_ptr);
		MFILE_munmap(old_mmap_ptr, old_mmap_size);
	}

	*mmap_size = 0;
	*mmap_ptr  = NULL;

	if (!length) {
		if (ftruncate(file_handle, ((off_t) 0)))
			return_code = -1;
	}
	else if (length <= *file_size) {
		if (((int) (tmp_mmap_ptr = ((void *) MFILE_mmap(old_mmap_ptr, length,
			mmap_prot, mmap_flags, file_handle, 0)))) == -1) {
			tmp_mmap_ptr = NULL;
			return_code  = -1;
		}
		else if ((length < *file_size) &&
			(ftruncate(file_handle, ((off_t) length))))
			return_code = -1;
	}
	else {
		if (((int) (tmp_mmap_ptr = ((void *) MFILE_mmap(old_mmap_ptr, length,
			mmap_prot, mmap_flags, file_handle, 0)))) == -1) {
			tmp_mmap_ptr = NULL;
			return_code  = -1;
		}
		else if (!safe_flag) {
			if (!ftruncate(file_handle, ((off_t) length)))
				file_size_changed_flag = 1;
			else
				return_code = -1;
		}
		else {
			memset(buffer, '\0', sizeof(buffer));
			file_size_changed_flag = 1;
			lseek(file_handle, ((off_t) old_mmap_size), SEEK_SET);
			for (count_1 = old_mmap_size; count_1 < length; ) {
				write_length = length - count_1;
				if (write_length >= sizeof(buffer)) {
					if (write_length % sizeof(buffer))
						write_length = write_length % sizeof(buffer);
					else
						write_length = sizeof(buffer);
				}
				if (write(file_handle, buffer, write_length) != write_length) {
					return_code = -1;
					break;
				}
				count_1 += write_length;
			}
		}
	}

	if (!return_code) {
		*file_size = length;
		*mmap_size = length;
		*mmap_ptr  = ((volatile void *) tmp_mmap_ptr);
		if (current_offset != NULL)
			*current_offset = (*current_offset > length) ? length :
				*current_offset;
	}
	else {
		if (tmp_mmap_ptr != NULL)
			MFILE_munmap(tmp_mmap_ptr, length);
		if (file_size_changed_flag &&
			ftruncate(file_handle, ((off_t) old_mmap_size))) {
			*file_size        = length;
			*fatal_error_flag = 1;
		}
		else if (((int) (old_mmap_ptr = ((void *) MFILE_mmap(old_mmap_ptr,
			old_mmap_size, mmap_prot, mmap_flags, file_handle, 0)))) == -1)
			*fatal_error_flag = 1;
		else {
			*mmap_size = old_mmap_size;
			*mmap_ptr  = old_mmap_ptr;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int mtruncate_basic_2(int file_handle, unsigned long *file_size,
	unsigned long *mmap_size, volatile void **mmap_ptr,
	unsigned long *current_offset, int mmap_prot, int mmap_flags,
	unsigned long length, int safe_flag, int *fatal_error_flag)
#else
int mtruncate_basic_2(file_handle, file_size, mmap_size, mmap_ptr,
	current_offset, mmap_prot, mmap_flags, length, safe_flag, fatal_error_flag)
int             file_handle;
unsigned long  *file_size;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   length;
int             safe_flag;
int            *fatal_error_flag;
#endif /* #ifndef NARGS */
{
	*fatal_error_flag = 0;

	return(0);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

#ifdef TEST_MAIN

#include <genfuncs.h>

#define TEST_FILE								"ERASE.ME3"
#define TEST_COUNT							100
#define TEST_SIZE								((unsigned int) 10000000L)

#undef  TEST_SIZE
#define TEST_SIZE								((unsigned int) 1000000L)

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code = 0;
	MFILE          *mfile_ptr   = NULL;
	unsigned int    count_1;
	unsigned long   total_size;
	struct timeval  start_time;
	struct timeval  end_time;

	fprintf(stderr, "Text routine for function 'mtruncate_basic_1()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------\n\n");

	if ((mfile_ptr = mopen(TEST_FILE, "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output file '%s'.\n\n",
			TEST_FILE);
		return_code = -1;
	}
	else {
		do {
			total_size = TEST_SIZE;
			GEN_GetTimeUSecs(&start_time);
			for (count_1 = 0; count_1 < TEST_COUNT; count_1++,
				total_size += TEST_SIZE) {
				if (mtruncate_basic_1(mfile_ptr, total_size, 1)) {
					fprintf(stderr, "ERROR: %s '%s' to %lu bytes.\n\n",
						"Unable to 'mtruncate_basic_1()' file", TEST_FILE,
						total_size);
					return_code = -1;
					break;
				}
			}
			if (return_code)
				break;
			GEN_GetTimeUSecs(&end_time);
			fprintf(stderr, "NEW 'mtruncate_safe()': %10.6f seconds.\n",
				(((double) GEN_GET_TIMEVAL_USECS(&end_time)) -
				((double) GEN_GET_TIMEVAL_USECS(&start_time))) / 1000000.0);
#if 1
break;
#endif /* #if 0 */
			if (mtruncate_safe(mfile_ptr, 0)) {
				fprintf(stderr, "ERROR: %s '%s' to %u bytes.\n\n",
					"Unable to 'mtruncate_basic_1()' file", TEST_FILE, 0);
				return_code = -1;
				break;
			}
			total_size = TEST_SIZE;
			GEN_GetTimeUSecs(&start_time);
			for (count_1 = 0; count_1 < TEST_COUNT; count_1++,
				total_size += TEST_SIZE) {
				if (mtruncate_safe(mfile_ptr, total_size)) {
					fprintf(stderr, "ERROR: %s '%s' to %lu bytes.\n\n",
						"Unable to 'mtruncate_safe()' file", TEST_FILE, total_size);
					return_code = -1;
					break;
				}
			}
			if (return_code)
				break;
			GEN_GetTimeUSecs(&end_time);
			fprintf(stderr, "OLD 'mtruncate_safe()': %10.6f seconds.\n",
				(((double) GEN_GET_TIMEVAL_USECS(&end_time)) -
				((double) GEN_GET_TIMEVAL_USECS(&start_time))) / 1000000.0);
		} while (!return_code);
		mclose(mfile_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

