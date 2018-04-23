/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMAP Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

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
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "mmap.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckAddress(address, error_text)
const void *address;
char       *error_text;
{
	int return_code = MMAP_SUCCESS;

	if (address == NULL) {
		if (error_text != NULL)
			strcpy(error_text,
				"Bad argument --- 'address' parameter is 'NULL'.");
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckLength(length, error_text)
unsigned int  length;
char         *error_text;
{
	int return_code = MMAP_SUCCESS;

	if (!length) {
		if (error_text != NULL)
			strcpy(error_text,
				"Bad argument --- 'length' parameter is '0'.");
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckAdvice(advice, error_text)
unsigned int  advice;
char         *error_text;
{
	int return_code = MMAP_SUCCESS;

	if ((advice != MMAP_MADV_NORMAL)     &&
		 (advice != MMAP_MADV_RANDOM)     &&
		 (advice != MMAP_MADV_SEQUENTIAL) &&
		 (advice != MMAP_MADV_WILLNEED)   &&
		 (advice != MMAP_MADV_DONTNEED)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'advice' parameter (%u = %08X).",
				advice, advice);
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckProtect(protect, error_text)
unsigned int  protect;
char         *error_text;
{
	int return_code = MMAP_SUCCESS;

	if ((protect != MMAP_PROT_NONE)     &&
		(!(protect & (MMAP_PROT_READ | MMAP_PROT_WRITE | MMAP_PROT_EXEC)))) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'protect' parameter (%u = %08X).",
				protect, protect);
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckSyncFlags(sync_flags, error_text)
unsigned int  sync_flags;
char         *error_text;
{
	int return_code = MMAP_SUCCESS;

	if ((sync_flags != MMAP_SYNC_ASYNC) &&
		 (sync_flags != MMAP_SYNC_SYNC)  &&
		 (sync_flags != MMAP_SYNC_INVALIDATE)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'sync_flags' parameter (%u = %08X).",
				sync_flags, sync_flags);
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_CheckMapFlags(map_flags, error_text)
unsigned int  map_flags;
char         *error_text;
{
	int return_code = MMAP_SUCCESS;

	if ((map_flags != MMAP_MMAP_SHARED)                          &&
		 (map_flags != (MMAP_MMAP_SHARED  | MMAP_MMAP_FIXED))     &&
		 (map_flags != (MMAP_MMAP_SHARED  | MMAP_MMAP_NORESERVE)) &&
		 (map_flags != (MMAP_MMAP_SHARED  | MMAP_MMAP_FIXED |
		MMAP_MMAP_NORESERVE))                                     &&
		 (map_flags != MMAP_MMAP_PRIVATE)                         &&
		 (map_flags != (MMAP_MMAP_PRIVATE | MMAP_MMAP_FIXED))     &&
		 (map_flags != (MMAP_MMAP_PRIVATE | MMAP_MMAP_NORESERVE)) &&
		 (map_flags != (MMAP_MMAP_PRIVATE | MMAP_MMAP_FIXED |
		MMAP_MMAP_NORESERVE))) {
		if (error_text != NULL)
			sprintf(error_text,
				"Bad argument --- invalid 'map_flags' parameter (%u = %08X).",
				map_flags, map_flags);
		return_code = MMAP_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

