/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a Sybase numeric type to a 'double'.

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
/*	***********************************************************************	*/

#include <stdio.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_NumberToDouble(int dbc_type, const void *number_ptr,
	double *double_ptr, char *error_text)
#else
int DBC_SYB_NumberToDouble(dbc_type, number_ptr, double_ptr, error_text)
int         dbc_type;
const void *number_ptr;
double     *double_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SYBINT1	:
			*double_ptr =
				((double) ((unsigned int) *((unsigned const char *) number_ptr)));
			break;
		case SYBINT2	:
			*double_ptr = ((double) *((const short *) number_ptr));
			break;
		case SYBINT4	:
			*double_ptr = ((double) *((const long *) number_ptr));
			break;
		case SYBREAL	:
			*double_ptr = ((double) *((const float *) number_ptr));
			break;
		case SYBFLT8	:
			*double_ptr = *((const double *) number_ptr);
			break;
		case SYBMONEY4	:
			*double_ptr =
				DBC_SYB_DBMONEY4ToDouble(((const DBMONEY4 *) number_ptr));
			break;
		case SYBMONEY	:
			*double_ptr =
				DBC_SYB_DBMONEYToDouble(((const DBMONEY *) number_ptr));
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC-number-to-double conversion function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

