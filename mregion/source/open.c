/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a file using 'open()' semantics.

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

#include <mbcompat.h>

#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _Windows
# include <io.h>
#endif /* #ifdef _Windows */

#include <genfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*
	CODE NOTE: To be moved into 'mregion.h'.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MRG_OPEN_CREATE_PERMS			(S_IREAD | S_IWRITE)
# undef MRG_OPEN_CREATE_PERMS
# define MRG_OPEN_CREATE_PERMS			420
#else
# define MRG_OPEN_CREATE_PERMS			(S_IRUSR | S_IWUSR)
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_OpenFile(const char *file_name, MRG_OPEN_MODE open_mode,
	MRG_FIL **fil_ptr, char *error_text)
#else
int MRG_OpenFile(file_name, open_mode, fil_ptr, error_text)
const char      *file_name;
MRG_OPEN_MODE    open_mode;
MRG_FIL        **fil_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	MRG_OPEN_MODE_OS os_open_mode;
	MMI_FLAG         mmap_flags;
	MMI_FLAG         prot_flags;
	char             n_1[STR_VAL2STR_MAX_LEN + 1];
	char             n_2[STR_VAL2STR_MAX_LEN + 1];
	char             n_3[STR_VAL2STR_MAX_LEN + 1];

	*fil_ptr = NULL;

	if ((file_name == NULL) || (!(*file_name))) {
		if (error_text != NULL)
			strcat(strcpy(error_text, "Invalid file name parameter: "),
				(file_name == NULL) ? "'NULL' string." : "zero-length string.");
		return_code = MRG_BAD_ARGS_FAILURE;
	}
	else if ((return_code = MRG_GetFlagsForOpen(open_mode, &os_open_mode,
		&mmap_flags, &prot_flags, error_text)) == MRG_SUCCESS) {
		if ((return_code = MRG_AllocateFil(fil_ptr, error_text)) ==
			MRG_SUCCESS) {
			if (((*fil_ptr)->file_name = strdup(file_name)) != NULL) {
#ifdef _Windows
				if (((*fil_ptr)->file_handle =
					open(file_name, os_open_mode, MRG_OPEN_CREATE_PERMS)) != -1) {
#else
				if (((*fil_ptr)->file_handle =
					open(file_name, os_open_mode, MRG_OPEN_CREATE_PERMS)) != -1) {
#endif /* #ifdef _Windows */
					(*fil_ptr)->open_mode    = open_mode;
					(*fil_ptr)->os_open_mode = os_open_mode;
					(*fil_ptr)->mmap_flags   = mmap_flags;
					(*fil_ptr)->prot_flags   = prot_flags;
					return_code              = MRG_GetFileSize(*fil_ptr,
						error_text);
				}
				else {
					if (error_text != NULL) {
						strcat(strcat(strcat(strcat(strcat(strcat(strcat(nstrcat(
							strcpy(error_text,
							"Unable to open file '"),
							file_name, 500),
							"' with MREGION open mode 0x"),
							val2str(((unsigned long) open_mode), 0, 16, "", n_1)),
							" native operating system open mode 0x"),
							val2str(((unsigned long) os_open_mode), 0, 16, "", n_2)),
							" and file creation mask 0x"),
							val2str(((unsigned long) MRG_OPEN_CREATE_PERMS), 0, 16,
							"", n_3)),
							": ");
						GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT / 2,
							error_text);
					}
					return_code = MRG_SYSTEM_FAILURE;
				}
			}
			else {
				STR_AllocMsgItem(strlen(file_name) + 1, error_text,
					"Unable to allocate memory for the open request file name");
				return_code = MRG_MEMORY_FAILURE;
			}
		}
		if (return_code != MRG_SUCCESS) {
			MRG_CloseFil(*fil_ptr);
			*fil_ptr = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

int main(void);

int main()
{
	int            return_code = MRG_SUCCESS;
	unsigned int   mode_count  = 0;
	MRG_MODE_ITEM *mode_list   = NULL;
	MRG_FIL       *fil_ptr     = NULL;
	unsigned int   count_1;
	char           file_name[256];
	char           error_text[MRG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MRG_OpenFile()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	if ((return_code = MRG_CopyModeList(&mode_count, &mode_list,
		error_text)) == MRG_SUCCESS) {
		for (count_1 = 0; count_1 < mode_count; count_1++) {
			sprintf(file_name, "TEST_OPEN_%s.xxx", mode_list[count_1].fopen_mode);
			fprintf(stderr, "Trying 'open(\"%s\", 0x%lx = \"%s\")' equivalent ",
				file_name, mode_list[count_1].open_mode,
				mode_list[count_1].fopen_mode);
			if ((return_code = MRG_OpenFile(file_name,
				mode_list[count_1].open_mode, &fil_ptr, error_text)) ==
				MRG_SUCCESS) {
				fprintf(stderr, " --- OK\n");
				MRG_CloseFil(fil_ptr);
			}
			else {
				fprintf(stderr, " --- FAILED\n");
				fprintf(stderr, "*** OPEN ERROR: %s\n", error_text);
			}
		}
		free(mode_list);
	}

	if (return_code != MRG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

