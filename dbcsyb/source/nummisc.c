/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Miscellaneous Sybase numeric type functions.

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

#include <float.h>
#include <limits.h>
#include <stdio.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_IsNumber(int dbc_type)
#else
int DBC_SYB_IsNumber(dbc_type)
int dbc_type;
#endif /* #ifndef NARGS */
{
	return(((dbc_type == SYBINT1) || (dbc_type == SYBINT2) ||
		(dbc_type == SYBINT4) || (dbc_type == SYBREAL) ||
		(dbc_type == SYBFLT8) || (dbc_type == SYBMONEY4) ||
		(dbc_type == SYBMONEY)) ? DBC_TRUE : DBC_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_MinNumber(int dbc_type, double *double_ptr, char *error_text)
#else
int DBC_SYB_MinNumber(dbc_type, double_ptr, error_text)
int     dbc_type;
double *double_ptr;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SYBINT1	:
			*double_ptr = ((double) 0.0);
			break;
		case SYBINT2	:
			*double_ptr = ((double) SHRT_MIN);
			break;
		case SYBINT4	:
			*double_ptr = ((double) LONG_MIN);
			break;
		case SYBREAL	:
			*double_ptr = ((double) FLT_MIN);
			break;
		case SYBFLT8	:
			*double_ptr = DBL_MIN;
			break;
		case SYBMONEY4	:
			*double_ptr = ((double) LONG_MIN) / 10000.0;
			break;
		case SYBMONEY	:
			*double_ptr = 922337203685477.5807;
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC number 'mininum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_MaxNumber(int dbc_type, double *double_ptr, char *error_text)
#else
int DBC_SYB_MaxNumber(dbc_type, double_ptr, error_text)
int     dbc_type;
double *double_ptr;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SYBINT1	:
			*double_ptr = ((double) UCHAR_MAX);
			break;
		case SYBINT2	:
			*double_ptr = ((double) SHRT_MAX);
			break;
		case SYBINT4	:
			*double_ptr = ((double) LONG_MAX);
			break;
		case SYBREAL	:
			*double_ptr = ((double) FLT_MAX);
			break;
		case SYBFLT8	:
			*double_ptr = DBL_MAX;
			break;
		case SYBMONEY4	:
			*double_ptr = ((double) LONG_MAX) / 10000.0;
			break;
		case SYBMONEY	:
			*double_ptr = 922337203685477.5808;
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC number 'maxinum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

