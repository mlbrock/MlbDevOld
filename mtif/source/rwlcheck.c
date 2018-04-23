/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a reader/writer lock for validity.

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
int MTIF_RWL_Check(const MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_Check(rwl_handle_ptr, error_text)
const MTIF_RWL_HANDLE *rwl_handle_ptr;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_Check(rwl_handle_ptr, "reader/writer lock",
		sizeof(*rwl_handle_ptr), offsetof(MTIF_RWL_HANDLE, signature),
		MTIF_RWL_SIGNATURE, error_text));
}
/* *********************************************************************** */

