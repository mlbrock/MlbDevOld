/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a file using 'fopen()' semantics and maps
								the file as a region (if it doesn't have 0-length).

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_FOpenFileWithMap(const char *file_name, const char *fopen_mode,
	MRG_FIL **fil_ptr, char *error_text)
#else
int MRG_FOpenFileWithMap(file_name, fopen_mode, fil_ptr, error_text)
const char  *file_name;
const char  *fopen_mode;
MRG_FIL    **fil_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	MRG_OPEN_MODE open_mode;

	*fil_ptr = NULL;

	if ((return_code = MRG_GetFlagsForFOpen(fopen_mode, &open_mode, NULL,
		NULL, NULL, error_text)) == MRG_SUCCESS)
		return_code = MRG_OpenFileWithMap(file_name, open_mode, fil_ptr,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code = MRG_SUCCESS;
	unsigned int   mode_count  = 0;
	MRG_MODE_ITEM *mode_list   = NULL;
	MRG_FIL       *fil_ptr     = NULL;
	unsigned int   count_1;
	unsigned int   count_2;
	char           error_text[MRG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MRG_FOpenFileWithMap()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------------\n\n");

	if (argc == 1) {
		sprintf(error_text,
			"Invalid usage.\n\nUSAGE:\n   %s <file-name> [<file-name> . . . ]",
			argv[0]);
		return_code = MRG_BAD_ARGS_FAILURE;
	}
	else if ((return_code = MRG_CopyModeList(&mode_count, &mode_list,
		error_text)) == MRG_SUCCESS) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			for (count_2 = 0; count_2 < mode_count; count_2++) {
				fprintf(stderr, "Open attempt for '%s', mode = '%s'",
					argv[count_1], mode_list[count_2].fopen_mode);
				if ((return_code = MRG_FOpenFileWithMap(argv[count_1],
					mode_list[count_2].fopen_mode, &fil_ptr, error_text)) ==
					MRG_SUCCESS) {
					if (fil_ptr->region_count)
						fprintf(stderr,
							" --- OK (file length = %lu, mmap length = %lu)\n",
							fil_ptr->file_length,
							fil_ptr->region_list[0]->mmap_length);
					else
						fprintf(stderr,
							" --- OK (file length = %lu, mmap length = N/A)\n",
							fil_ptr->file_length);
					MRG_CloseFil(fil_ptr);
					fil_ptr = NULL;
				}
				else {
					fprintf(stderr, " --- FAILED\n");
					fprintf(stderr, "*** FOPEN ERROR: %s\n", error_text);
				}
			}
		}
		free(mode_list);
	}

	if (return_code != MRG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

