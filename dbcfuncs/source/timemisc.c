/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic miscellaneous DBC facility time type
								functions.

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
int DBC_IsTime(const DBC_CONTEXT *dbc_context_ptr, int dbc_type)
#else
int DBC_IsTime(dbc_context_ptr, dbc_type)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_FALSE;

	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.is_time), NULL) ==
		DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.is_time)(dbc_type);

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_MinTime(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	DTIME *dtime_ptr, char *error_text)
#else
int DBC_MinTime(dbc_context_ptr, dbc_type, dtime_ptr, error_text)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
DTIME             *dtime_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.min_time),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.min_time)
			(dbc_type, dtime_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_MaxTime(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	DTIME *dtime_ptr, char  *error_text)
#else
int DBC_MaxTime(dbc_context_ptr, dbc_type, dtime_ptr, error_text)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
DTIME             *dtime_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.max_time),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.max_time)
			(dbc_type, dtime_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

