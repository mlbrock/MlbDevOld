/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats various DBC facility data-types.

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
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_FormatType(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	unsigned int data_length, const void *data_ptr, unsigned int min_length,
	unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string, char *error_text)
#else
int DBC_FormatType(dbc_context_ptr, dbc_type, data_length, data_ptr,
	min_length, max_length, right_justify_flag, decimal_places, out_string,
	error_text)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
unsigned int       data_length;
const void        *data_ptr;
unsigned int       min_length;
unsigned int       max_length;
int                right_justify_flag;
unsigned int       decimal_places;
char              *out_string;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.format_type),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.format_type)
			(dbc_type, data_length, data_ptr, min_length, max_length,
			right_justify_flag, decimal_places, out_string, error_text);

	return(return_code);
}
/* *********************************************************************** */


