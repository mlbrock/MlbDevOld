/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MRG Memory-mapped Region Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Memory-maps a region.

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
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <genfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_MapReg(MMI_FILE_HANDLE file_handle, MMI_ADDRESS base_address,
	MMI_LENGTH mmap_length, MMI_OFFSET mmap_offset, MMI_FLAG mmap_flags,
	MMI_FLAG prot_flags, MRG_REG **reg_ptr, char *error_text)
#else
int MRG_MapReg(file_handle, base_address, mmap_length, mmap_offset,
	mmap_flags, prot_flags, reg_ptr, error_text)
MMI_FILE_HANDLE   file_handle;
MMI_ADDRESS       base_address;
MMI_LENGTH        mmap_length;
MMI_OFFSET        mmap_offset;
MMI_FLAG          mmap_flags;
MMI_FLAG          prot_flags;
MRG_REG         **reg_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char mmi_error_text[MMI_MAX_ERROR_TEXT];

	if ((return_code = MRG_AllocateReg(reg_ptr, error_text)) == MRG_SUCCESS) {
/*
	CODE NOTE: To be fixed --- and probably removed.
		mmap_length =
			((MMI_LENGTH) STRFUNCS_ADJUST_SIZE(mmap_length, MMI_GetPageSize()));
*/
		if ((return_code = MMI_Map(base_address, mmap_length, prot_flags,
			(mmap_flags) ? mmap_flags : MMI_FLAG_MMAP_SHARED, file_handle,
			mmap_offset, &(*reg_ptr)->mmap_ptr, &(*reg_ptr)->os_mmap_handle,
			(error_text != NULL) ? mmi_error_text : NULL)) == MMI_SUCCESS) {
			(*reg_ptr)->base_address = base_address;
			(*reg_ptr)->mmap_length  = mmap_length;
			(*reg_ptr)->mmap_offset  = mmap_offset;
			(*reg_ptr)->mmap_flags   = mmap_flags;
			(*reg_ptr)->prot_flags   = prot_flags;
			return_code              = MRG_MAP_ERROR_MMI(return_code);
		}
		else {
			if (error_text != NULL)
				nstrcpy(error_text, mmi_error_text, MRG_MAX_ERROR_TEXT - 1);
			MRG_CloseReg(*reg_ptr);
			*reg_ptr    = NULL;
			return_code = MRG_MAP_ERROR_MMI(return_code);
		}
	}

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
	int           return_code = MRG_SUCCESS;
	FILE         *file_ptr    = NULL;
	MRG_REG      *reg_ptr     = NULL;
	unsigned int  count_1;
	struct stat   stat_data;
	char          error_text[MRG_MAX_ERROR_TEXT];

void *mmap_ptr;

	fprintf(stderr, "Test harness for function 'MRG_MapReg()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------\n\n");

if ((file_ptr = fopen("XXX", "r+")) == NULL) {
	sprintf(error_text, "Unable to 'fopen()' file 'XXX': ");
	GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT / 2,
		error_text);
	return_code = MRG_SYSTEM_FAILURE;
	goto EXIT_FUNCTION;
}
if ((return_code = MMI_Map(NULL, 8192, MMI_FLAG_PROT_RW,
	MMI_FLAG_MMAP_SHARED, fileno(file_ptr), 0, &mmap_ptr,
	NULL, error_text)) == MMI_SUCCESS) {
	fprintf(stderr, "*** A direct call to 'MMI_Map()' succeeded.\n");
	fclose(file_ptr);
}
else {
	fprintf(stderr, "*** A direct call to 'MMI_Map()' failed: %s\n",
		error_text);
	return_code = MRG_SYSTEM_FAILURE;
	goto EXIT_FUNCTION;
}

	if (argc == 1) {
		sprintf(error_text,
			"Invalid usage.\n\nUSAGE:\n   %s <file-name> [<file-name> . . . ]",
			argv[0]);
		return_code = MRG_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "Open attempt for '%s'", argv[count_1]);
			if ((file_ptr = fopen(argv[count_1], "r+")) == NULL) {
				sprintf(error_text, "Unable to 'fopen()' file '%-.500s': ",
					argv[count_1]);
				GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT / 2,
					error_text);
				return_code = MRG_SYSTEM_FAILURE;
				break;
			}
			if (fstat(fileno(file_ptr), &stat_data)) {
				sprintf(error_text, "Error on 'fstat(\"%s\" = %d, 0x%lx): ",
					argv[count_1], fileno(file_ptr),
					((unsigned long) &stat_data));
				GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT / 2,
					error_text);
				return_code = MRG_SYSTEM_FAILURE;
				break;
			}
			if ((return_code = MRG_MapReg(fileno(file_ptr), NULL,
				((MMI_LENGTH) stat_data.st_size), 0, MMI_FLAG_MMAP_SHARED,
				MMI_FLAG_PROT_RW, &reg_ptr, error_text)) == MRG_SUCCESS) {
				fprintf(stderr,
					" --- OK (mmap length = %lu)\n",
					reg_ptr->mmap_length);
				MRG_CloseReg(reg_ptr);
			}
			else {
				fprintf(stderr, " --- FAILED\n");
if (MMI_Map(NULL, 8192, MMI_FLAG_PROT_RW,
	MMI_FLAG_MMAP_SHARED, fileno(file_ptr), 0, &mmap_ptr,
	NULL, error_text) == MMI_SUCCESS)
	fprintf(stderr, "*** But a direct call to 'MMI_Map()' succeeded.\n");
else
	fprintf(stderr, "*** And a direct call to 'MMI_Map()' failed: %s\n",
		error_text);
				break;
			}
			fclose(file_ptr);
		}
	}

EXIT_FUNCTION:

	if (return_code != MRG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

