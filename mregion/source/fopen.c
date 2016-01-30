/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a file using 'fopen()' semantics.

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
int MRG_FOpenFile(const char *file_name, const char *fopen_mode,
	MRG_FIL **fil_ptr, char *error_text)
#else
int MRG_FOpenFile(file_name, fopen_mode, fil_ptr, error_text)
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
		return_code = MRG_OpenFile(file_name, open_mode, fil_ptr, error_text);

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

	fprintf(stderr, "Test harness for function 'MRG_FOpenFile()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

	if ((return_code = MRG_CopyModeList(&mode_count, &mode_list,
		error_text)) == MRG_SUCCESS) {
		for (count_1 = 0; count_1 < mode_count; count_1++) {
			sprintf(file_name, "TEST_FOPEN_%s.xxx", mode_list[count_1].fopen_mode);
			fprintf(stderr, "Trying 'fopen(\"%s\", \"%s\")' equivalent ",
				file_name, mode_list[count_1].fopen_mode);
			if ((return_code = MRG_FOpenFile(file_name,
				mode_list[count_1].fopen_mode, &fil_ptr, error_text)) ==
				MRG_SUCCESS) {
				fprintf(stderr, " --- OK\n");
				MRG_CloseFil(fil_ptr);
			}
			else {
				fprintf(stderr, " --- FAILED\n");
				fprintf(stderr, "*** FOPEN ERROR: %s\n", error_text);
			}
		}
		free(mode_list);
	}

	if (return_code != MRG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

