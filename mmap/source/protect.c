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

#include <genfuncs.h>

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
int MMAP_Protect(address, length, protect, error_text)
void         *address;
unsigned int  length;
unsigned int  protect;
char         *error_text;
{
	int  return_code = MMAP_SUCCESS;
	char tmp_error_text[MMAP_MAX_ERROR_TEXT];

	if (((return_code =
		MMAP_CheckAddress(address, tmp_error_text)) == MMAP_SUCCESS) &&
		 ((return_code =
		MMAP_CheckLength(length, tmp_error_text))   == MMAP_SUCCESS) &&
		 ((return_code =
		MMAP_CheckProtect(protect, tmp_error_text)) == MMAP_SUCCESS)) {
		if (MMAP_mprotect(address, length, protect))
			return_code = MMAP_SYSTEM_FAILURE;
		if ((return_code != MMAP_SUCCESS) && (error_text != NULL))
			GEN_GetLastErrorString(0, MMAP_MAX_ERROR_TEXT, tmp_error_text);
	}

	if ((return_code != MMAP_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "MMAP_Protect(%08lX, %u, %u, %08lX) failed: %s",
			((unsigned long) address), length, protect,
			((unsigned long) error_text), tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

