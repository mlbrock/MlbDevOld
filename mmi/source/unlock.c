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

#include <genfuncs.h>

#include "mmii.h"

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

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_Unlock(MMI_ADDRESS address, MMI_LENGTH length, char *error_text)
#else
int MMI_Unlock(address, length, error_text)
MMI_ADDRESS  address;
MMI_LENGTH   length;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MMI_SUCCESS;
	char tmp_error_text[MMI_MAX_ERROR_TEXT];

	if (((return_code =
		MMI_CheckAddress(address, tmp_error_text)) == MMI_SUCCESS) &&
		 ((return_code =
		MMI_CheckLength(length, tmp_error_text))   == MMI_SUCCESS)) {
		if (MMI_munlock(address, length))
			return_code = MMI_SYSTEM_FAILURE;
		if ((return_code != MMI_SUCCESS) && (error_text != NULL))
			GEN_GetLastErrorString(0, MMI_MAX_ERROR_TEXT, tmp_error_text);
	}

	if ((return_code != MMI_SUCCESS) && (error_text != NULL))
		sprintf(error_text,
			"%s(%s = 0x%lx, %s = %lu, %s = 0x%lx) failed: %s",
			"MMI_Unlock",
			"address", ((unsigned long) address),
			"length", length,
			"error_text", ((unsigned long) error_text),
			tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

