/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Handles formatted output to a memory-mapped file.

	Revision History	:	1992-08-25 --- Creation.
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

#include <limits.h>
#include <string.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mprintf

   SYNOPSIS    :  bytes_output = mprintf(MFILE *mfile_ptr,
							const char *in_format, ...);

						int         bytes_output;

						MFILE      *mfile_ptr;

						const char *in_format;

   DESCRIPTION :  Writes data to a memory-mapped file as specified by the
						``in_format`` parameter and any subsequent parameters
						(if any).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``in_format`` is a ``printf()`` format specified.

						(.) ``...`` subsequent arguments to this function (if any)
						are output in accordance with the specifications embedded
						in the ``in_format`` parameter.

   RETURNS     :  Returns from this function are as follow:

						(.) The number of bytes output by this function if
						successful.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fprintf()``.

   CAVEATS     :  This function uses the function ``vsprintf()`` to perform
						the actual work of formatting the output. Therefore, the
						exact nature of the formatted output may vary according to
						the compatibility with the ANSI C standard of the local
						C library implementation of that function.

   SEE ALSO    :  vmprintf

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mprintf
						Memory-mapped File Functions:printf Functions:mprintf
						MFILE Functions:mprintf

	PUBLISH XREF:	mprintf

	PUBLISH NAME:	mprintf

	ENTRY CLASS	:	Memory-mapped File Functions:printf Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
int mprintf(MFILE *mfile_ptr, const char *in_format, ...)
#else
int mprintf(mfile_ptr, in_format, va_alist)
MFILE      *mfile_ptr;
const char *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     char_count = 0;
	va_list argument_ptr;

	if (mprintf_ensure_space(mfile_ptr) != MFILE_FALSE) {
#ifndef NO_STDARGS
		va_start(argument_ptr, in_format);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
#ifndef MFILE_MMAP_NON_NATIVE
		vsprintf(((char *) mfile_ptr->mmap_ptr) +
           mfile_ptr->current_offset, in_format, argument_ptr);
		/* ********************************************************	*/
		/* ********************************************************	*/
		/* 	We take the length of the formatted output string		*/
		/* below because we can't depend upon the return value from	*/
		/* 'vsprintf()' --- pre-ANSI compilers returned a pointer	*/
		/* the buffer rather than the number of characters minus		*/
		/* the terminating ASCII zero.										*/
		/* ********************************************************	*/
		char_count = strlen(((char *) mfile_ptr->mmap_ptr) +
			mfile_ptr->current_offset);
		/* ********************************************************	*/
#else
		char_count = vfprintf(mfile_ptr->file_ptr, in_format, argument_ptr);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
		va_end(argument_ptr);
		if (char_count > 0) {
			mfile_ptr->mfile_flags    |= MFILE_FLAG_WRITTEN;
			mfile_ptr->current_offset += char_count;
			mfile_ptr->file_size       =
				(mfile_ptr->current_offset > mfile_ptr->file_size) ?
				mfile_ptr->current_offset : mfile_ptr->file_size;
		}
	}

	return(char_count);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mprintf_ensure_space

   SYNOPSIS    :  truth_flag = mprintf_ensure_space(MFILE *mfile_ptr);

						int    truth_flag;

						MFILE *mfile_ptr;

   DESCRIPTION :  Ensures that there is sufficient space in the memory-mapped
						file to support the minimum ``mprintf`` buffer size. The
						minimum ``mprintf`` buffer size is defined by the value of
						the manifest constant ''MFILE_PRINTF_BUFFER_SIZE''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''MFILE_TRUE'' if there is sufficient space.

						(.) Otherwise, the function returns ''MFILE_FALSE''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  MFILE_EnsureSpace
						mprintf

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mprintf_ensure_space
						Memory-mapped File Functions:printf Functions:mprintf_ensure_space
						MFILE Functions:mprintf_ensure_space

	PUBLISH XREF:	mprintf_ensure_space

	PUBLISH NAME:	mprintf_ensure_space

	ENTRY CLASS	:	Memory-mapped File Functions:printf Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mprintf_ensure_space(MFILE *mfile_ptr)
#else
int mprintf_ensure_space(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int           has_space_flag = MFILE_FALSE;
	unsigned long buffer_size;
	unsigned long new_size;

	if ((mfile_ptr != NULL) && (!MFILE_ValidateMFILEPtr(mfile_ptr)) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		buffer_size = (mfile_ptr->buffer_size > MFILE_PRINTF_BUFFER_SIZE) ?
			mfile_ptr->buffer_size : MFILE_PRINTF_BUFFER_SIZE;
		if ((new_size = (mfile_ptr->mmap_size - mfile_ptr->current_offset)) <
			MFILE_PRINTF_BUFFER_SIZE_MIN) {
			new_size = mfile_ptr->mmap_size + buffer_size;
			if (!mtruncate_safe(mfile_ptr, new_size)) {
				mfile_ptr->file_size = mfile_ptr->current_offset;
 				has_space_flag       = MFILE_TRUE;
			}
		}
		else
			has_space_flag = MFILE_TRUE;
	}

	return(has_space_flag);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	MFILE        *m_file_ptr  = NULL;
	unsigned int  in_count    = 0;
	unsigned int  line_count  = 0;
	int           out_count;
	char         *fgets_return;
	char          buffer[512];

	fprintf(stderr, "Test routine for 'mprintf()'\n");
	fprintf(stderr, "---- ------- --- -----------\n\n");

	if ((m_file_ptr = mopen("ERASE.ME", "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output file 'ERASE.ME'.\n\n");
		return_code = -1;
	}
	else {
		while ((!feof(stdin)) && (!ferror(stdin))) {
			*buffer      = '\0';
			fgets_return = buffer;
			while (fgets_return && (!(*buffer))) {
				fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
				in_count++;
			}
			if ((!fgets_return) || (!strnicmp(buffer, "END", 3))) {
				fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
					"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
				break;
			}
out_count = mprintf(m_file_ptr, "%s", buffer); line_count++;
		}
		mclose(m_file_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

