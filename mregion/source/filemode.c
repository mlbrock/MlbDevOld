/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the mapping between 'fopen()' modes,
								MREGION 'open()' modes, native operating system
								'open()' modes, memory-mapping flags and
								memory-mapping protection flags.

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

#include <fcntl.h>
#include <string.h>

#include <strfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions private to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void MRG_SetFlags,
	(const MRG_MODE_ITEM *mode_ptr, MRG_OPEN_MODE *open_mode,
	MRG_OPEN_MODE_OS *os_open_mode, MMI_FLAG *mmap_flags,
	MMI_FLAG *prot_flags));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The supported fopen() and open() modes . . .										*/
/*	***********************************************************************	*/
static const MRG_MODE_ITEM MRG_ModeList[] = {
	{	"a",
			MRG_FOPEN_MODE_A,
			O_APPEND | O_CREAT | O_RDWR,
			0,
			MMI_FLAG_PROT_WRITE	},
	{	"ab",
			MRG_FOPEN_MODE_A,
			O_APPEND | O_CREAT | O_RDWR,
			0,
			MMI_FLAG_PROT_WRITE	},
	{	"a+",
			MRG_FOPEN_MODE_AP,
			O_APPEND | O_CREAT | O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"ab+",
			MRG_FOPEN_MODE_AP,
			O_APPEND | O_CREAT | O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"a+b",
			MRG_FOPEN_MODE_AP,
			O_APPEND | O_CREAT | O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"r",
			MRG_FOPEN_MODE_R,
			O_RDONLY,
			0,
			MMI_FLAG_PROT_READ	},
	{	"rb",
			MRG_FOPEN_MODE_R,
			O_RDONLY,
			0,
			MMI_FLAG_PROT_READ	},
	{	"r+",
			MRG_FOPEN_MODE_RP,
			O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"rb+",
			MRG_FOPEN_MODE_RP,
			O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"r+b",
			MRG_FOPEN_MODE_RP,
			O_RDWR,
			0,
			MMI_FLAG_PROT_RW	},
	{	"w",
			MRG_FOPEN_MODE_W,
			O_CREAT  | O_TRUNC | O_RDWR,
			0,
			MMI_FLAG_PROT_WRITE	},
	{	"wb",
			MRG_FOPEN_MODE_W,
			O_CREAT  | O_TRUNC | O_RDWR,
			0,
			MMI_FLAG_PROT_WRITE	},
	{	"w+",
			MRG_FOPEN_MODE_WP,
			O_CREAT  | O_RDWR  | O_TRUNC,
			0,
			MMI_FLAG_PROT_RW	},
	{	"wb+",
			MRG_FOPEN_MODE_WP,
			O_CREAT  | O_RDWR  | O_TRUNC,
			0,
			MMI_FLAG_PROT_RW	},
	{	"w+b",
			MRG_FOPEN_MODE_WP,
			O_CREAT  | O_RDWR  | O_TRUNC,
			0,
			MMI_FLAG_PROT_RW	}
};

static const unsigned int  MRG_ModeCount  =
	sizeof(MRG_ModeList) / sizeof(MRG_ModeList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_CopyModeList(unsigned int *mode_count, MRG_MODE_ITEM **mode_list,
	char *error_text)
#else
int MRG_CopyModeList(mode_count, mode_list, error_text)
unsigned int   *mode_count;
MRG_MODE_ITEM **mode_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	*mode_count = 0;
	*mode_list  = NULL;

	if ((*mode_list = ((MRG_MODE_ITEM *)
		calloc(MRG_ModeCount, sizeof(MRG_MODE_ITEM)))) != NULL) {
		memcpy(*mode_list, MRG_ModeList, MRG_ModeCount * sizeof(MRG_MODE_ITEM));
		*mode_count = MRG_ModeCount;
		return_code = MRG_SUCCESS;
	}
	else {
		if (error_text != NULL)
			STR_AllocMsgList(MRG_ModeCount, sizeof(MRG_MODE_ITEM), error_text,
				"Unable to copy the MREGION file open mode list");
		return_code = MRG_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_GetFlagsForFOpen(const char *fopen_mode, MRG_OPEN_MODE *open_mode,
	MRG_OPEN_MODE_OS *os_open_mode, MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags,
	char *error_text)
#else
int MRG_GetFlagsForFOpen(fopen_mode, open_mode, os_open_mode, mmap_flags,
	prot_flags, error_text)
const char       *fopen_mode;
MRG_OPEN_MODE    *open_mode;
MRG_OPEN_MODE_OS *os_open_mode;
MMI_FLAG         *mmap_flags;
MMI_FLAG         *prot_flags;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MRG_FAILURE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < MRG_ModeCount; count_1++) {
		if (!strcmp(MRG_ModeList[count_1].fopen_mode, fopen_mode)) {
			MRG_SetFlags(MRG_ModeList + count_1, open_mode,
				os_open_mode, mmap_flags, prot_flags);
			return_code = MRG_SUCCESS;
			break;
		}
	}

	if ((return_code != MRG_SUCCESS) && (error_text != NULL))
		strcat(nstrcat(strcpy(error_text, "Unable to locate 'fopen()' mode ('"),
			fopen_mode, MRG_MAX_ERROR_TEXT / 2), "').");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_GetFlagsForOpen(MRG_OPEN_MODE open_mode,
	MRG_OPEN_MODE_OS *os_open_mode, MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags,
   char *error_text)
#else
int MRG_GetFlagsForOpen(open_mode, os_open_mode, mmap_flags, prot_flags,
	error_text)
MRG_OPEN_MODE     open_mode;
MRG_OPEN_MODE_OS *os_open_mode;
MMI_FLAG         *mmap_flags;
MMI_FLAG         *prot_flags;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MRG_FAILURE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < MRG_ModeCount; count_1++) {
		if (MRG_ModeList[count_1].open_mode == open_mode) {
			MRG_SetFlags(MRG_ModeList + count_1, NULL, os_open_mode, mmap_flags,
				prot_flags);
			return_code = MRG_SUCCESS;
			break;
		}
	}

	if ((return_code != MRG_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "Unable to locate 'open()' mode (%lu = 0x%lx).",
			open_mode, open_mode);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_GetFlagsForOpenOS(MRG_OPEN_MODE_OS os_open_mode,
	MRG_OPEN_MODE *open_mode, MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags,
	char *error_text)
#else
int MRG_GetFlagsForOpenOS(os_open_mode, open_mode, mmap_flags, prot_flags,
	error_text)
MRG_OPEN_MODE_OS  os_open_mode;
MRG_OPEN_MODE    *open_mode;
MMI_FLAG         *mmap_flags;
MMI_FLAG         *prot_flags;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MRG_FAILURE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < MRG_ModeCount; count_1++) {
		if (MRG_ModeList[count_1].os_open_mode == os_open_mode) {
			MRG_SetFlags(MRG_ModeList + count_1, open_mode, NULL, mmap_flags,
				prot_flags);
			return_code = MRG_SUCCESS;
			break;
		}
	}

	if ((return_code != MRG_SUCCESS) && (error_text != NULL))
		sprintf(error_text,
			"Unable to locate operating system 'open()' mode (%d = 0x%lx).",
			os_open_mode, ((unsigned long) os_open_mode));

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void MRG_SetFlags(const MRG_MODE_ITEM *mode_ptr,
	MRG_OPEN_MODE *open_mode, MRG_OPEN_MODE_OS *os_open_mode,
	MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags)
#else
static void MRG_SetFlags(mode_ptr, open_mode, os_open_mode, mmap_flags,
	prot_flags)
const MRG_MODE_ITEM *mode_ptr;
MRG_OPEN_MODE       *open_mode;
MRG_OPEN_MODE_OS    *os_open_mode;
MMI_FLAG            *mmap_flags;
MMI_FLAG            *prot_flags;
#endif /* #ifndef NARGS */
{
	if (open_mode != NULL)
		*open_mode = mode_ptr->open_mode;

	if (os_open_mode != NULL)
		*os_open_mode = mode_ptr->os_open_mode;

	if (mmap_flags != NULL)
		*mmap_flags = mode_ptr->mmap_flags;

	if (prot_flags != NULL)
		*prot_flags = mode_ptr->prot_flags;
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <genfuncs.h>

int main(void);

int main()
{
	int            return_code = MRG_SUCCESS;
	unsigned int   mode_count  = 0;
	MRG_MODE_ITEM *mode_list   = NULL;
	unsigned int   count_1;
	char           file_name[256];
	FILE          *file_ptr;
	char           error_text[MRG_MAX_ERROR_TEXT];

	if ((return_code = MRG_CopyModeList(&mode_count, &mode_list,
		error_text)) == MRG_SUCCESS) {
		for (count_1 = 0; count_1 < mode_count; count_1++) {
			sprintf(file_name, "TEST_%s.xxx", mode_list[count_1].fopen_mode);
			fprintf(stderr, "Trying 'fopen(%s, %s)",
				file_name, mode_list[count_1].fopen_mode);
			if ((file_ptr = fopen(file_name, mode_list[count_1].fopen_mode)) !=
				NULL) {
				fclose(file_ptr);
				fprintf(stderr, " --- OK\n");
			}
			else {
				fprintf(stderr, " --- FAILED\n");
				sprintf(error_text, "Unable to open test file '%s': ", file_name);
				GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT - 100, error_text);
				return_code = MRG_SYSTEM_FAILURE;
			}
		}
		free(mode_list);
	}

	if (return_code != MRG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

