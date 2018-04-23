/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks once-only initialization lock for validity.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <stddef.h>
#include <string.h>

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_ONC_Check(const MTIF_ONC_HANDLE *once_ptr, char *error_text)
#else
int MTIF_ONC_Check(once_ptr, error_text)
const MTIF_ONC_HANDLE *once_ptr;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_SUPP_Check(once_ptr, "once control",
		sizeof(*once_ptr), offsetof(MTIF_ONC_HANDLE, signature),
		MTIF_ONC_SIGNATURE, error_text)) == MTIF_SUCCESS) {
		if (((return_code = MTIF_MTX_Check(&once_ptr->mtx_data,
			(error_text != NULL) ? tmp_error_text : NULL)) != MTIF_SUCCESS) &&
			(error_text != NULL))
			strcat(strcpy(error_text,
				"Once control handle mutex lock problem: "), tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

