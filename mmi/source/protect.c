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

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_Protect(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	char *error_text)
#else
int MMI_Protect(address, length, prot_flags, error_text)
MMI_ADDRESS  address;
MMI_LENGTH   length;
MMI_FLAG     prot_flags;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int      return_code = MMI_SUCCESS;
	MMI_FLAG os_prot_flags;
	char     tmp_error_text[MMI_MAX_ERROR_TEXT];

	if (((return_code =
		MMI_CheckAddress(address, tmp_error_text)) == MMI_SUCCESS) &&
		 ((return_code =
		MMI_CheckLength(length, tmp_error_text))   == MMI_SUCCESS) &&
		 ((return_code =
		MMI_CheckProtect(prot_flags, tmp_error_text)) == MMI_SUCCESS)) {
		os_prot_flags = MMI_MAP_FLAG_PROT_TO_OS(prot_flags);
		if (MMI_mprotect(address, length, os_prot_flags))
			return_code = MMI_SYSTEM_FAILURE;
		if ((return_code != MMI_SUCCESS) && (error_text != NULL))
			GEN_GetLastErrorString(0, MMI_MAX_ERROR_TEXT, tmp_error_text);
	}

	if ((return_code != MMI_SUCCESS) && (error_text != NULL))
		sprintf(error_text,
			"%s(%s = 0x%lx, %s = %lu, %s = %lu, %s = 0x%lx) failed: %s",
			"MMI_Protect",
			"address", ((unsigned long) address),
			"length", length,
			"prot_flags", prot_flags,
			"error_text", ((unsigned long) error_text),
			tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

