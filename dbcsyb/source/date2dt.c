/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a Sybase date type to a DATFUNCS 'DTIME'
								structure date.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_DateToDTIME(int dbc_type, const void *date_ptr, DTIME *dtime_ptr,
	char *error_text)
#else
int DBC_SYB_DateToDTIME(dbc_type, date_ptr, dtime_ptr, error_text)
int         dbc_type;
const void *date_ptr;
DTIME      *dtime_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SYBDATETIME4	:
			DBC_SYB_Sybase4ToDTIME(((const DBDATETIME4 *) date_ptr), dtime_ptr);
			break;
		case SYBDATETIME	:
			DBC_SYB_Sybase8ToDTIME(((const DBDATETIME *) date_ptr), dtime_ptr);
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC-date-to-DTIME conversion function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

