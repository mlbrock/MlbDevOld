/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic conversion of a DATFUNCS 'DTIME' structure
								to a DBC facility date type.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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
int DBC_DTIMEToDate(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	const DTIME *dtime_ptr, void *date_ptr, char *error_text)
#else
int DBC_DTIMEToDate(dbc_context_ptr, dbc_type, dtime_ptr, date_ptr,
	error_text)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
const DTIME       *dtime_ptr;
void              *date_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.dtime_to_date),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.dtime_to_date)
			(dbc_type, dtime_ptr, date_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

