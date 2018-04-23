/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic conversion of a DBC facility date type to
								a DATFUNCS 'DTIME' structure date.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_DateToDTIME(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	const void *date_ptr, DTIME *dtime_ptr, char *error_text)
#else
int DBC_DateToDTIME(dbc_context_ptr, dbc_type, date_ptr, dtime_ptr,
	error_text)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
const void        *date_ptr;
DTIME             *dtime_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.date_to_dtime),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.date_to_dtime)
			(dbc_type, date_ptr, dtime_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

