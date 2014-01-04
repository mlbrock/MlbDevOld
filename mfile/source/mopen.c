/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a memory-mapped file.

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

#include <memory.h>
#include <string.h>

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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	The variables below are used throughout the MFILE library functions.	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF MFILE        *MFILE_EntryList  = NULL;
COMPAT_EXTERN_DATA_DEF unsigned int  MFILE_EntryCount = 0;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mopen

   SYNOPSIS    :  mfile_ptr = mopen(file_name, file_mode);

						MFILE      *mfile_ptr;

						const char *file_name;

						const char *file_mode;

   DESCRIPTION :  Opens the file specified by the ``file_name`` parameter
						for memory-mapped access. If the file exists and has a
						file length greater than zero, the file is mapped into
						the address space of the invoking process.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``file_name`` is the name of the file to be opened.

						(.) ``file_mode`` is the in which the file ``file_name`` is to
						be opened. At the present time, the following modes are
						supported:

						(..) ``r`` to open the file for reading.

						(..) ``w`` to open the file writing. Note that if the file
						already exists, it will be truncated to zero-length upon
						the open.

						(..) ``r+`` to open a file for reading and writing.

   RETURNS     :  Returns from this function are as follow:

						(.) A pointer to the ''MFILE'' structure representing the
						file if the open succeeds.

						(.) ''NULL'' if an error occurred.

   NOTES       :  This function is the memory-mapped file library analogue of
						the ANSI C level two I/O function ``fopen()``.

   CAVEATS     :  

   SEE ALSO    :  mclose

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	mopen
						Memory-mapped File Functions:Open Functions:mopen
						MFILE Functions:mopen

	PUBLISH XREF:	mopen

	PUBLISH NAME:	mopen

	ENTRY CLASS	:	Memory-mapped File Functions:Open Functions

EOH */
#ifndef MFILE_MMAP_NON_NATIVE
/* *********************************************************************** */
#ifndef NARGS
MFILE *mopen(const char *file_name, const char *file_mode)
#else
MFILE *mopen(file_name, file_mode)
const char *file_name;
const char *file_mode;
#endif /* #ifndef NARGS */
{
	MFILE                 *return_ptr = NULL;
	unsigned int           count_1;
	int                    mode_index = -1;
	MFILE                 *tmp_ptr;
	MFILE                 *mfile_ptr  = NULL;
	const MFILE_MODE_ITEM *mode_ptr   = NULL;
	struct stat            stat_data;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (!(MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE)) {
			mfile_ptr = MFILE_EntryList + count_1;
			break;
		}
	}

	if (!mfile_ptr) {
		if (!MFILE_EntryList) {
			if ((MFILE_EntryList = ((MFILE *) calloc(1024, sizeof(MFILE))))) {
				mfile_ptr        = MFILE_EntryList;
				MFILE_EntryCount = 1024;
			}
		}
/*
		if (!MFILE_EntryCount)
			tmp_ptr = ((MFILE *) malloc(sizeof(MFILE)));
		else
			tmp_ptr = ((MFILE *) realloc(MFILE_EntryList,
				(MFILE_EntryCount + 1) * sizeof(MFILE)));
		if (tmp_ptr) {
			memset(tmp_ptr + MFILE_EntryCount, '\0', sizeof(MFILE));
			MFILE_EntryList = tmp_ptr;
			mfile_ptr       = MFILE_EntryList + MFILE_EntryCount;
			MFILE_EntryCount++;
		}
*/
	}

	if (mfile_ptr && (mode_ptr = MFILE_ValidateMFILEMode(file_mode))) {
		mfile_ptr->mfile_flags = mode_ptr->mfile_mode;
		mfile_ptr->mmap_mode   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_prot   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_flags  = MAP_SHARED;
		if ((mfile_ptr->file_name = strdup(file_name)) != NULL) {
			if ((mfile_ptr->file_ptr = fopen(file_name,
				mode_ptr->real_mode_name)) != NULL) {
				if ((strcmp(mode_ptr->real_mode_name, mode_ptr->mode_name)) &&
					(fclose(mfile_ptr->file_ptr) || ((mfile_ptr->file_ptr =
					fopen(file_name, mode_ptr->mode_name)) == NULL)))
					mfile_ptr->file_ptr = NULL;
				else if (!stat(mfile_ptr->file_name, &stat_data)) {
					mfile_ptr->file_size = stat_data.st_size;
					if (!mfile_ptr->file_size)
						return_ptr = mfile_ptr;
					else if (((int) (mfile_ptr->mmap_ptr =
						((char *) MFILE_mmap(NULL, stat_data.st_size,
						mfile_ptr->mmap_prot, mfile_ptr->mmap_flags,
						fileno(mfile_ptr->file_ptr), 0)))) != -1) {
						mfile_ptr->mmap_size              = stat_data.st_size;
						return_ptr                        = mfile_ptr;
					}
				}
			}
		}
		if (return_ptr)
			return_ptr->mfile_flags = mode_ptr->mfile_mode | MFILE_FLAG_IN_USE;
		else {
			if (mfile_ptr->file_ptr) {
				fclose(mfile_ptr->file_ptr);
				if (strcmp(file_mode, "w"))
					unlink(mfile_ptr->file_name);
			}
			if (mfile_ptr->file_name)
				free(mfile_ptr->file_name);
			memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
		}
	}

	return(return_ptr);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
MFILE *mopen(const char *file_name, const char *file_mode)
#else
MFILE *mopen(file_name, file_mode)
const char *file_name;
const char *file_mode;
#endif /* #ifndef NARGS */
{
	MFILE                 *return_ptr = NULL;
	MFILE                 *mfile_ptr  = NULL;
	unsigned int           count_1;
	const MFILE_MODE_ITEM *mode_ptr;
	struct stat            stat_data;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (!(MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE)) {
			mfile_ptr = MFILE_EntryList + count_1;
			break;
		}
	}

	if (!mfile_ptr) {
		if (!MFILE_EntryList) {
			if ((MFILE_EntryList = ((MFILE *) calloc(64, sizeof(MFILE)))) !=
				NULL) {
				mfile_ptr        = MFILE_EntryList;
				MFILE_EntryCount = 64;
			}
		}
	}

	if (mfile_ptr && ((mode_ptr = MFILE_ValidateMFILEMode(file_mode)) !=
		NULL)) {
		mfile_ptr->mfile_flags = mode_ptr->mfile_mode;
		mfile_ptr->mmap_mode   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_prot   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_flags  = 0;
		if ((mfile_ptr->file_name = strdup(file_name)) != NULL) {
			if ((mfile_ptr->file_ptr = fopen(file_name,
				mode_ptr->real_mode_name)) != NULL) {
				if ((strcmp(mode_ptr->real_mode_name, mode_ptr->mode_name)) &&
					(fclose(mfile_ptr->file_ptr) || ((mfile_ptr->file_ptr =
					fopen(file_name, mode_ptr->mode_name)) == NULL)))
					mfile_ptr->file_ptr = NULL;
				else if (!stat(mfile_ptr->file_name, &stat_data)) {
					mfile_ptr->file_size = stat_data.st_size;
					return_ptr           = mfile_ptr;
				}
			}
		}
		if (return_ptr)
			return_ptr->mfile_flags = mode_ptr->mfile_mode | MFILE_FLAG_IN_USE;
		else {
			if (mfile_ptr->file_ptr) {
				fclose(mfile_ptr->file_ptr);
				if (strcmp(file_mode, "w"))
					unlink(mfile_ptr->file_name);
			}
			if (mfile_ptr->file_name)
				free(mfile_ptr->file_name);
			memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
		}
	}

	return(return_ptr);
}
/* *********************************************************************** */
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int    return_code = 0;
	MFILE *m_file_ptr  = NULL;
	char  *fgets_return;
	char   buffer[512];

	fprintf(stderr, "Text routine for function 'mopen()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------\n\n");

	if ((m_file_ptr = mopen("ERASE.ME2", "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output file 'ERASE.ME2'.\n\n");
		return_code = -1;
	}
	else {
		msetbuf(m_file_ptr, 65536);
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
			mwrite(buffer, sizeof(char), strlen(buffer), m_file_ptr);
/*
			fprintf(stderr, "mwrite() returns: %d\n",
				mwrite(buffer, sizeof(char), strlen(buffer), m_file_ptr));
*/
/*			fprintf(stderr, "mflush() returns: %d\n", mflush(m_file_ptr)); */
		}
		mclose(m_file_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

