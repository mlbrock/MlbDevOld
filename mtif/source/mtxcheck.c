/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a basic mutex for validity.

	Revision History	:	1994-09-03 --- Creation.
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

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTX_Check(const MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text)
#else
int MTIF_MTX_Check(mtx_handle_ptr, error_text)
const MTIF_MTX_HANDLE *mtx_handle_ptr;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_Check(mtx_handle_ptr, "non-recusive mutex",
		sizeof(*mtx_handle_ptr), offsetof(MTIF_MTX_HANDLE, signature),
		MTIF_MTX_SIGNATURE, error_text));
}
/* *********************************************************************** */

