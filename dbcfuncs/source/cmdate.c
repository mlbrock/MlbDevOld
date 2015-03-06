/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic comparison of DBC facility date types.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
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
int DBC_CompareDate(const DBC_CONTEXT *dbc_context_ptr, int dbc_type,
	const void *ptr_1, const void *ptr_2)
#else
int DBC_CompareDate(dbc_context_ptr, dbc_type, ptr_1, ptr_2)
const DBC_CONTEXT *dbc_context_ptr;
int                dbc_type;
const void        *ptr_1;
const void        *ptr_2;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.cmp_date), NULL) ==
		DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.cmp_date)
			(dbc_type, ptr_1, ptr_2);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_SCompareDate(const DBC_CONTEXT *dbc_context_ptr, void *control_ptr,
	const void *ptr_1, const void *ptr_2, size_t data_length)
#else
int DBC_SCompareDate(dbc_context_ptr, control_ptr, ptr_1, ptr_2, data_length)
const DBC_CONTEXT *dbc_context_ptr;
void              *control_ptr;
const void        *ptr_1;
const void        *ptr_2;
size_t             data_length;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.scmp_date), NULL) ==
		DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.scmp_date)
			(control_ptr, ptr_1, ptr_2, data_length);

	return(return_code);
}
/* *********************************************************************** */

