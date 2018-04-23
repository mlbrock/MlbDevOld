/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Writes blocks to a memory-mapped file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

   NAME        :  mwrite

   SYNOPSIS    :  element_count = mwrite(data_ptr, element_size,
							element_count, mfile_ptr);

						int           element_count;

						const void   *data_ptr;

						unsigned int  element_size;

						unsigned int  element_count;

						MFILE        *mfile_ptr;

   DESCRIPTION :  Copies ``element_count`` blocks of size ``element_size``
						from the area of memory to which ``data_ptr`` points to
						memory-mapped file specified by ``mfile_ptr``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_ptr`` points to the area of memory from which the
						data copied into the memory-mapped file is located.

						(.) ``element_size`` is the size of each of the blocks to be
						copied to the memory-mapped file.

						(.) ``element_count`` is the number of blocks to be copied
						to the memory-mapped file.

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  The number of complete blocks copied to the memory-mapped
						file.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fwrite()``.

   CAVEATS     :  

   SEE ALSO    :  mread

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	mwrite
						Memory-mapped File Functions:mwrite
						MFILE Functions:mwrite

	PUBLISH XREF:	mwrite

	PUBLISH NAME:	mwrite

	ENTRY CLASS	:	Memory-mapped File Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
int mwrite(const void *data_ptr, unsigned int element_size,
	unsigned int element_count, MFILE *mfile_ptr)
#else
int mwrite(data_ptr, element_size, element_count, mfile_ptr)
const void   *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int record_count = 0;
	unsigned int byte_count;

	byte_count = element_size * element_count;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
		byte_count = 0;
	else if (MFILE_EnsureSpace(mfile_ptr, mfile_ptr->buffer_size,
		byte_count, NULL) == MFILE_SUCCESS) {
		memcpy(((char *) mfile_ptr->mmap_ptr) + mfile_ptr->current_offset,
			data_ptr, byte_count);
		mfile_ptr->file_size      +=
			((mfile_ptr->current_offset + byte_count) > mfile_ptr->file_size) ?
			((mfile_ptr->current_offset + byte_count) - mfile_ptr->file_size) : 0;
		mfile_ptr->mfile_flags    |= MFILE_FLAG_WRITTEN;
		mfile_ptr->current_offset += byte_count;
		record_count               = element_count;
	}

	return(record_count);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
int mwrite(const void *data_ptr, unsigned int element_size,
	unsigned int element_count, MFILE *mfile_ptr)
#else
int mwrite(data_ptr, element_size, element_count, mfile_ptr)
const void   *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
#endif /* #ifndef NARGS */
{
	unsigned long  byte_count;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
		byte_count = 0;
	else
		byte_count = fwrite(data_ptr, element_size, element_count,
			mfile_ptr->file_ptr) * element_size;

	mfile_ptr->current_offset += byte_count;

	return(((unsigned int) (byte_count / ((unsigned long) element_size))));
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

#ifdef TEST_MAIN
 
COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	MFILE        *m_file_ptr  = NULL;
	unsigned int  line_count  = 0;
	char         *fgets_return;
	char          buffer[512];

	fprintf(stderr, "Test routine for 'mwrite()'\n");
	fprintf(stderr, "---- ------- --- -----------\n\n");

	if ((m_file_ptr = mopen("ERASE.ME", "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output file 'ERASE.ME'.\n\n");
		return_code = -1;
	}
	else {
		while ((!feof(stdin)) && (!ferror(stdin))) {
			*buffer      = '\0';
			fgets_return = buffer;
			while (fgets_return && (!(*buffer)))
				fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
			if ((!fgets_return) || (!strnicmp(buffer, "END", 3))) {
				fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
					"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
				break;
			}
			if (mwrite(buffer, strlen(buffer), 1, m_file_ptr) != 1) {
				mclose(m_file_ptr);
				fprintf(stderr, "ERROR: %s %u %s.\n\n",
					"Unable to 'mwrite()'", strlen(buffer),
					"butes to output file 'ERASE.ME'");
				return_code = -1;
				break;
			}
			line_count++;
		}
		mclose(m_file_ptr);
		fprintf(stderr, "\n\n%u lines written to 'ERASE.ME'.\n\n", line_count);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

