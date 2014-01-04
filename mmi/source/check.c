/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

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
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "mmii.h"

/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckAddress(const MMI_ADDRESS address, char *error_text)
#else
int MMI_CheckAddress(address, error_text)
const MMI_ADDRESS  address;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if (address == NULL) {
		if (error_text != NULL)
			strcpy(error_text,
				"Bad argument --- 'address' parameter is 'NULL'.");
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckLength(MMI_LENGTH length, char *error_text)
#else
int MMI_CheckLength(length, error_text)
MMI_LENGTH  length;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if (!length) {
		if (error_text != NULL)
			strcpy(error_text,
				"Bad argument --- 'length' parameter is '0'.");
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckAdvice(MMI_FLAG madv_flags, char *error_text)
#else
int MMI_CheckAdvice(madv_flags, error_text)
MMI_FLAG  madv_flags;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if ((madv_flags != MMI_FLAG_MADV_NORMAL)     &&
		 (madv_flags != MMI_FLAG_MADV_RANDOM)     &&
		 (madv_flags != MMI_FLAG_MADV_SEQUENTIAL) &&
		 (madv_flags != MMI_FLAG_MADV_WILLNEED)   &&
		 (madv_flags != MMI_FLAG_MADV_DONTNEED)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'madv_flags' parameter (%lu = 0x%lx).",
				madv_flags, madv_flags);
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckProtect(MMI_FLAG prot_flags, char *error_text)
#else
int MMI_CheckProtect(prot_flags, error_text)
MMI_FLAG  prot_flags;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if ((prot_flags != MMI_FLAG_PROT_NONE) &&
		(!(prot_flags & (MMI_FLAG_PROT_READ | MMI_FLAG_PROT_WRITE |
		MMI_FLAG_PROT_EXEC)))) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'prot_flags' parameter (%lu = 0x%lx).",
				prot_flags, prot_flags);
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckSyncFlags(MMI_FLAG sync_flags, char *error_text)
#else
int MMI_CheckSyncFlags(sync_flags, error_text)
MMI_FLAG  sync_flags;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if ((sync_flags != MMI_FLAG_SYNC_ASYNC) &&
		 (sync_flags != MMI_FLAG_SYNC_SYNC)  &&
		 (sync_flags != MMI_FLAG_SYNC_INVALIDATE)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'sync_flags' parameter (%lu = 0x%lx).",
				sync_flags, sync_flags);
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_CheckMapFlags(MMI_FLAG mmap_flags, char *error_text)
#else
int MMI_CheckMapFlags(mmap_flags, error_text)
MMI_FLAG  mmap_flags;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MMI_SUCCESS;

	if ((mmap_flags != MMI_FLAG_MMAP_SHARED)                              &&
		 (mmap_flags != (MMI_FLAG_MMAP_SHARED  | MMI_FLAG_MMAP_FIXED))     &&
		 (mmap_flags != (MMI_FLAG_MMAP_SHARED  | MMI_FLAG_MMAP_NORESERVE)) &&
		 (mmap_flags != (MMI_FLAG_MMAP_SHARED  | MMI_FLAG_MMAP_FIXED |
		MMI_FLAG_MMAP_NORESERVE))                                          &&
		 (mmap_flags != MMI_FLAG_MMAP_PRIVATE)                             &&
		 (mmap_flags != (MMI_FLAG_MMAP_PRIVATE | MMI_FLAG_MMAP_FIXED))     &&
		 (mmap_flags != (MMI_FLAG_MMAP_PRIVATE | MMI_FLAG_MMAP_NORESERVE)) &&
		 (mmap_flags != (MMI_FLAG_MMAP_PRIVATE | MMI_FLAG_MMAP_FIXED |
		MMI_FLAG_MMAP_NORESERVE))) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'map_flags' parameter (%lu = 0x%lx).",
				mmap_flags, mmap_flags);
		return_code = MMI_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

