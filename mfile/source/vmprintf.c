/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Handles formatted output to a memory-mapped file
								using a variable argument list.

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

#include <string.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  vmprintf

   SYNOPSIS    :  bytes_output = vmprintf(MFILE *mfile_ptr,
							const char *in_format, arg_list);

						int         bytes_output;

						MFILE      *mfile_ptr;

						const char *in_format;

						va_list     arg_list;

   DESCRIPTION :  Writes data to a memory-mapped file as specified by the
						``in_format`` parameter and the subsequent parameters
						encapsulated within the ``arg_list`` parameter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``in_format`` is a ``printf()`` format specified.

						(.) ``arg_list`` contains subsequent arguments to this
						function. They will be output in accordance with the
						specifications embedded in the ``in_format`` parameter.

   RETURNS     :  Returns from this function are as follow:

						(.) The number of bytes output by this function if
						successful.

						(.) The value of the manifest constant ''EOF'' if
						an error occurs.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``vfprintf()``.

   CAVEATS     :  This function uses the function ``vsprintf()`` to perform
						the actual work of formatting the output. Therefore, the
						exact nature of the formatted output may vary according to
						the compatibility with the ANSI C standard of the local
						C library implementation of that function.

   SEE ALSO    :	mprintf

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	vmprintf
						Memory-mapped File Functions:printf Functions:vmprintf
						MFILE Functions:vmprintf

	PUBLISH XREF:	vmprintf

	PUBLISH NAME:	vmprintf

	ENTRY CLASS	:	Memory-mapped File Functions:printf Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int vmprintf(MFILE *mfile_ptr, const char *in_format, va_list arg_list)
#else
int vmprintf(mfile_ptr, in_format, arg_list)
MFILE      *mfile_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	int char_count = 0;

	if (mprintf_ensure_space(mfile_ptr) != MFILE_FALSE) {
#ifndef MFILE_MMAP_NON_NATIVE
		vsprintf(((char *) mfile_ptr->mmap_ptr) +
           mfile_ptr->current_offset, in_format, arg_list);
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
		char_count = vfprintf(mfile_ptr->file_ptr, in_format, arg_list);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
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

	fprintf(stderr, "Test routine for 'vmprintf()'\n");
	fprintf(stderr, "---- ------- --- ------------\n\n");

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

