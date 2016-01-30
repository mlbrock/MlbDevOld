/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a recursive mutex for validity.

	Revision History	:	1994-09-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_Check(const MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_Check(mtr_handle_ptr, error_text)
const MTIF_MTR_HANDLE *mtr_handle_ptr;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_Check(mtr_handle_ptr, "recusive mutex",
		sizeof(*mtr_handle_ptr), offsetof(MTIF_MTR_HANDLE, signature),
		MTIF_MTR_SIGNATURE, error_text));
}
/* *********************************************************************** */

